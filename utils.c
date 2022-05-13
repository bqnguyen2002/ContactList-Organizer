#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void upper (char str [])
{
    for(int i = 0; i < strlen(str); i++){
        if(str[i] >= 'a' && str[i] <= 'z'){
            // converts lower case to upper case letter
            str[i] = str[i] - 32;
        }
    }
}