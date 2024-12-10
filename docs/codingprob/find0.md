```c

#include <stdio.h>
char *match(char *s, char ch)

{
    if(s == NULL) return NULL;
    
    while(*s != '\0') {
        if(*s == ch) {
            return s;
        }
        s++;
    }
    return NULL;
}
int main(void )
{
    char ch, str[80], *p = NULL;

    scanf("%s", str);
    getchar(); 
    ch = getchar();  
    if((p = match(str, ch)) != NULL)  
        printf("%s\n", p);
    else 
        printf("Not Found\n");
    return 0;
}

```