#include <stdio.h>
#define HEIGHT 17
int main ( ) {
int i = 0;
int n = 0;
char ch;
while (i < HEIGHT) {
    for(n = 7, n> i, n--)
    {
        printf(" ");
    }
printf("I\n");
//printf("III\n");
i = i + 1;
}
ch = getchar( ); /* stops the console window from disappearing */
}
