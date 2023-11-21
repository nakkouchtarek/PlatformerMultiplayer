#include <global.h>
#include <stdio.h>

void change_time()
{
    int index = 5;

    char str[10] = {0};
    
    sprintf(str, "%d", (int)seconds);

	// Add level to our first string
    for(short i=0;i<strlen(str);i++)
    {
        time_count[index]=str[i];
		index++;
    }
}