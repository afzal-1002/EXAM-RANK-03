const canvas = document.getElementById('main-canvas');
const ctx = canvas.getContext('2d');
const letterInput = document.getElementById('letter-input');
const fileInput = document.getElementById('file-input');
const completionMessage = document.getElementById('completion-message');

let width, height;
let particles = [];
let codeLines = [];
let nextLineIndex = 0;
let isCodeMode = false;
let score = 0;
let finalAlignmentX = null;
const scoreDisplay = document.getElementById('score-counter');
const CM_IN_PX = 37.8;
const FINAL_LEFT_SHIFT = 3 * CM_IN_PX;
let completionStartTime = null;

// Audio Context for synthesized sounds
let audioCtx = null;

function playSuccessSound() {
    if (!audioCtx) audioCtx = new (window.AudioContext || window.webkitAudioContext)();

    const now = audioCtx.currentTime;

    // Primary "thud" oscillator
    const osc1 = audioCtx.createOscillator();
    const gain1 = audioCtx.createGain();
    osc1.type = 'sine';
    osc1.frequency.setValueAtTime(150, now);
    osc1.frequency.exponentialRampToValueAtTime(40, now + 0.2);

    gain1.gain.setValueAtTime(0.3, now);
    gain1.gain.exponentialRampToValueAtTime(0.001, now + 0.2);

    // Harmonic highlight
    const osc2 = audioCtx.createOscillator();
    const gain2 = audioCtx.createGain();
    osc2.type = 'triangle';
    osc2.frequency.setValueAtTime(300, now);
    osc2.frequency.setValueAtTime(450, now + 0.05);

    gain2.gain.setValueAtTime(0.05, now);
    gain2.gain.exponentialRampToValueAtTime(0.001, now + 0.1);

    osc1.connect(gain1);
    gain1.connect(audioCtx.destination);
    osc2.connect(gain2);
    gain2.connect(audioCtx.destination);

    osc1.start();
    osc2.start();
    osc1.stop(now + 0.2);
    osc2.stop(now + 0.1);
}

function playLevelCompleteSound() {
    if (!audioCtx) audioCtx = new (window.AudioContext || window.webkitAudioContext)();
    const now = audioCtx.currentTime;

    // Classic 8-bit "tu-tu-tu-TUUU" fanfare
    // Frequencies: G4, G4, G4, C5 (classic rhythm)
    const notes = [
        { freq: 392.00, start: 0, dur: 0.1 },      // tu
        { freq: 392.00, start: 0.15, dur: 0.1 },   // tu
        { freq: 392.00, start: 0.30, dur: 0.1 },   // tu
        { freq: 523.25, start: 0.45, dur: 0.6 }    // TUUU
    ];

    notes.forEach(note => {
        const osc = audioCtx.createOscillator();
        const gain = audioCtx.createGain();

        // Square wave gives that distinct 8-bit / NES sound
        osc.type = 'square';
        osc.frequency.setValueAtTime(note.freq, now + note.start);

        gain.gain.setValueAtTime(0.06, now + note.start);
        gain.gain.setValueAtTime(0.06, now + note.start + note.dur - 0.02);
        gain.gain.linearRampToValueAtTime(0, now + note.start + note.dur);

        osc.connect(gain);
        gain.connect(audioCtx.destination);

        osc.start(now + note.start);
        osc.stop(now + note.start + note.dur);
    });
}

const PARTICLE_COUNT = 100;
const CODE_PARTICLE_COUNT = 30;
const FALL_SPEED = -0.2; // Negative for upward movement
const MOUSE_DISTANCE = 200;
const LETTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789{}[]";

let lastSpawnTime = 0;
let nextSpawnDelay = 2000; // 1-2 seconds randomly

window.addEventListener('resize', init);

// Focus input whenever user clicks anywhere on the page
window.addEventListener('click', (e) => {
    // Don't autofocus if clicking the file label
    if (e.target.id !== 'file-label') {
        letterInput.focus();
    }
});

// File Loading Logic
fileInput.addEventListener('change', (e) => {
    const file = e.target.files[0];
    if (!file) return;

    const reader = new FileReader();
    reader.onload = (event) => {
        const text = event.target.result;
        // Split into lines, remove empty lines, and ignore lines that are block comments (/* ... */)
        codeLines = text.split('\n').filter(line => {
            const trimmed = line.trim();
            if (trimmed.length === 0) return false;
            // Ignore lines starting with /* and ending with */
            if (trimmed.startsWith('/*') && trimmed.endsWith('*/')) return false;
            return true;
        });

        if (codeLines.length > 0) {
            isCodeMode = true;
            nextLineIndex = 0; // Reset index for the new file
            score = 0; // Reset score for new file
            finalAlignmentX = null; // Reset alignment
            completionStartTime = null; // Reset completion timer
            completionMessage.classList.remove('show');
            updateScore();
            letterInput.placeholder = "Type code snippet...";
            letterInput.maxLength = 500; // Allow much longer strings for code
            // Clear current particles to transition
            particles = [];
            init();
        }
    };
    reader.readAsText(file);
});

letterInput.addEventListener('keydown', (e) => {
    const pairs = {
        '(': ')',
        '{': '}',
        '[': ']'
    };

    // Auto-completion for pairs
    if (pairs[e.key]) {
        e.preventDefault();
        const start = e.target.selectionStart;
        const end = e.target.selectionEnd;
        const value = e.target.value;
        const closing = pairs[e.key];

        e.target.value = value.substring(0, start) + e.key + closing + value.substring(end);

        // Set cursor position between brackets
        e.target.selectionStart = e.target.selectionEnd = start + 1;
        return;
    }

    // Overtyping closing brackets
    const closingBrackets = [')', '}', ']'];
    if (closingBrackets.includes(e.key)) {
        const start = e.target.selectionStart;
        const value = e.target.value;
        if (value[start] === e.key) {
            e.preventDefault();
            e.target.selectionStart = e.target.selectionEnd = start + 1;
            return;
        }
    }

    if (e.key === 'Enter') {
        const rawValue = e.target.value.trim();
        if (rawValue) {
            let matched = false;
            // The "search string" is the user's full input without any spaces
            const searchStr = rawValue.toLowerCase().replace(/\s+/g, '');

            particles.forEach(p => {
                // The "target content" is the code line or letter without any spaces
                const targetContent = p.content.toLowerCase().replace(/\s+/g, '');

                // NEW LOGIC:
                // 1. Exact match (ignoring spaces)
                // 2. Exact match if we ignore a trailing semicolon or brace from the source
                const targetNoPunctuation = targetContent.replace(/[;{}]+$/, '');

                if ((targetContent === searchStr || targetNoPunctuation === searchStr) && !p.isExploding && !p.isTyped) {
                    p.explode();
                    matched = true;
                }
            });

            if (matched) {
                // Visual feedback: smooth green highlight on match
                letterInput.classList.remove('match-success');
                void letterInput.offsetWidth; // Trigger reflow
                letterInput.classList.add('match-success');
                setTimeout(() => letterInput.classList.remove('match-success'), 600);

                e.target.value = '';
                playSuccessSound();

                // Update score
                score++;
                updateScore();
            } else {
                // Visual feedback: smooth red horizontal fade for incorrect
                letterInput.classList.remove('match-error');
                void letterInput.offsetWidth; // Trigger reflow
                letterInput.classList.add('match-error');
                setTimeout(() => letterInput.classList.remove('match-error'), 600);
            }
        }
    }
});

function updateScore() {
    scoreDisplay.innerText = `lines typed: ${score}`;
}

function init() {
    width = canvas.width = window.innerWidth;
    height = canvas.height = window.innerHeight;

    const initialCount = isCodeMode ? Math.min(4, codeLines.length) : 20;

    if (particles.length < initialCount) {
        for (let i = particles.length; i < initialCount; i++) {
            if (isCodeMode && nextLineIndex >= codeLines.length) break;
            particles.push(new Particle(true, i));
        }
    }
}

class Particle {
    constructor(isInitial = false, index = 0) {
        // Lock in the mode when created
        this.type = isCodeMode ? 'code' : 'letter';
        this.spawnIndex = nextLineIndex; // Store spawn order
        this.targetY = -height; // Default off-screen top
        this.reset(isInitial, index);
    }

    reset(isInitial = false, initialIndex = 0) {
        // Prepare font to measure width
        if (this.type === 'code') {
            if (nextLineIndex < codeLines.length) {
                this.content = codeLines[nextLineIndex];
                this.spawnIndex = nextLineIndex; // Sync index
                nextLineIndex++;
            } else {
                // If we run out of code, this particle becomes a letter or dies
                this.type = 'letter';
                this.content = LETTERS[Math.floor(Math.random() * LETTERS.length)];
            }
            this.baseFontSize = 14 + Math.random() * 4;
        } else {
            this.content = LETTERS[Math.floor(Math.random() * LETTERS.length)];
            this.baseFontSize = 24 + Math.random() * 12;
        }

        this.fontSize = this.baseFontSize;
        ctx.font = `${this.fontSize}px 'Courier New'`;
        const textWidth = ctx.measureText(this.content).width;

        // Spread across horizontal but keep on screen
        const maxRange = Math.max(0, width - textWidth - 20);
        this.x = Math.random() * maxRange;

        if (this.type === 'code') {
            if (isInitial) {
                // To keep them in order while bubbling up:
                // Higher index lines must be lower on screen (larger Y)
                this.y = 300 + (initialIndex * 40);
            } else {
                this.y = height + 100;
            }
        } else {
            this.y = isInitial ? Math.random() * height : height + 100;
        }

        this.vy = FALL_SPEED;

        this.fontSize = this.baseFontSize;
        this.color = '#00ff41';
        this.glow = 0;
        this.opacity = Math.random() * 0.5 + 0.5;
        this.isExploding = false;
        this.explosionLife = 1;
        this.dead = false;
        this.isTyped = false;
        this.textWidth = textWidth;
    }

    explode() {
        this.isExploding = true;
        this.isTyped = true;
        this.explosionLife = 1.0;
        this.glow = 50;
    }

    update() {
        if (this.dead) return;

        if (this.isExploding) {
            this.explosionLife -= 0.05;
            this.fontSize += this.type === 'code' ? 0.2 : 2;
            this.vy *= 0.9;
            if (this.explosionLife <= 0) {
                this.isExploding = false; // Transition out of explosion
                if (this.type !== 'code') this.dead = true; // Only letters die
            }
        }

        // Center and shrink typed lines
        if (this.isTyped && this.type === 'code') {
            // If all lines are typed, align to the first line's left edge
            // Otherwise, center individually, but shifted 3cm left
            const targetX = (finalAlignmentX !== null) ? finalAlignmentX : (width - this.textWidth) / 2 - FINAL_LEFT_SHIFT;
            this.x += (targetX - this.x) * 0.1; // Smooth slide

            // Shrink by 10% (target 0.9 of original)
            const targetSize = this.baseFontSize * 0.9;
            if (this.fontSize > targetSize) {
                this.fontSize -= 0.1;
            }
        }

        // Apply upward "bubbling" logic
        if (this.y > this.targetY) {
            this.vy = FALL_SPEED; // Constant upward speed
            this.y += this.vy;
        } else {
            // Snap to target and stop
            this.y = this.targetY;
            this.vy = 0;
        }

        // Kill if it bubbles off the very top
        if (this.y < -100 && !this.isExploding) {
            this.dead = true;
        }

        if (this.fontSize > this.baseFontSize) {
            this.fontSize -= 1;
        }
        if (this.glow > 0) {
            this.glow -= 1;
        }
    }

    draw() {
        ctx.font = `${this.fontSize}px 'Courier New'`;

        if (this.isExploding) {
            ctx.fillStyle = `rgba(255, 255, 255, ${this.explosionLife})`;
            ctx.shadowBlur = this.glow * this.explosionLife;
            ctx.shadowColor = '#00ff41';
        } else if (this.isTyped && this.type === 'code') {
            // Dull gray for typed lines
            ctx.fillStyle = 'rgba(150, 150, 150, 0.4)';
            ctx.shadowBlur = 0;
        } else {
            ctx.fillStyle = this.color;
            ctx.globalAlpha = this.opacity;
            if (this.glow > 0) {
                ctx.shadowBlur = this.glow;
                ctx.shadowColor = '#00ff41';
            } else {
                ctx.shadowBlur = 0;
            }
        }

        ctx.fillText(this.content, this.x, this.y);
        ctx.globalAlpha = 1;
        ctx.shadowBlur = 0;
    }
}

function animate() {
    const now = Date.now();
    ctx.fillStyle = 'rgba(5, 5, 5, 0.15)';
    ctx.fillRect(0, 0, width, height);

    particles = particles.filter(p => !p.dead);

    // Calculate targetY for stacking code at the TOP
    if (isCodeMode) {
        // Check if we just finished all lines
        if (score > 0 && score >= codeLines.length && finalAlignmentX === null) {
            // Robust alignment: find ANY code particle to determine width if first line is gone
            const anyLine = particles.find(p => p.type === 'code');
            const referenceWidth = anyLine ? anyLine.textWidth : 400; // Fallback width
            finalAlignmentX = (width - referenceWidth) / 2 - FINAL_LEFT_SHIFT;
            completionStartTime = now;
        }

        // Show completion message 2 seconds after alignment starts
        if (completionStartTime && now - completionStartTime > 2000) {
            if (!completionMessage.classList.contains('show')) {
                completionMessage.classList.add('show');
                playLevelCompleteSound();
            }
        }

        // Sort active code particles (including typed ones) by their original order
        const activeCode = particles
            .filter(p => p.type === 'code')
            .sort((a, b) => a.spawnIndex - b.spawnIndex);

        let currentY = 30; // Starting stack position (10px buffer from top)
        activeCode.forEach(p => {
            p.targetY = currentY;
            currentY += (p.fontSize * 1.2 + 8); // 8px buffer
        });
    } else {
        // Reset targetY for non-code mode (top target)
        particles.forEach(p => p.targetY = -200);
    }

    const targetCount = isCodeMode ? CODE_PARTICLE_COUNT : PARTICLE_COUNT;

    // Spaced out spawning: adjusted to prevent overlap based on speed
    const canSpawnCode = !isCodeMode || (isCodeMode && nextLineIndex < codeLines.length);
    if (particles.length < targetCount && now - lastSpawnTime > nextSpawnDelay && canSpawnCode) {
        particles.push(new Particle(false));
        lastSpawnTime = now;
        // Calculation: (FontSize ~18 + Gap 10) / speed 0.2 * 16ms per frame approx 2.3s
        nextSpawnDelay = 2200 + Math.random() * 800;
    }

    particles.forEach(p => {
        p.update();
        p.draw();
    });

    requestAnimationFrame(animate);
}

init();
animate();
