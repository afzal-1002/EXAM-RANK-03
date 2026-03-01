#include <stdio.h>
#include <unistd.h>
#include <string.h>


char check_match(char* big_s, char* smal_s)
{
    int len;
    len = strlen(smal_s);
    int i=0;
    while (smal_s[i]== big_s[i] && i < len)
        i++;
    if (i == len) return 'Y';
    else return 'N';

}

int print_stars(const char *str)
 {
    int len;
    len = strlen(str);
    int i = 0;
    char c;

    c = '*';
    while (i < len)
    {
       write(1,&c,1);
        i++;
    }
    return i;
 }

int main (int argc, char *argv[])
{
    char buff[8000000];
    buff[0] = 0;
    buff[7999999] = 0;
    int i;
    i = 1;
    
    int chars_read;
    chars_read = 0;
    char *str;

    if (argc != 2)
        return 1;

    chars_read = read(0, &buff[0], 1);
    while(chars_read == 1 && i< 8000000)
    {
          chars_read = read(0, &buff[i], 1);
          i++;
    }
    //printf("buffer:%s",&buff[0]);
    
    str = argv[1];
    i = 0;
  while (buff[i])
    {
        if (str[0] == buff[i])
        {
            if (check_match(&buff[i],&str[0])== 'Y')
            {
                i = i + print_stars(&str[0]);
                //printf("XXX");
            }
            else
            {
                write(1,&buff[i],1);
                i++;
            } 
                
        }
        else{

        write(1,&buff[i],1);
        i++;
        }
    }  
    
    
    //printf("match:%c",check_match("ABCD", "ABCE"));
   //int stars = print_stars(str);
   //printf("stars:%i",stars);
    
  


return 0;
}
