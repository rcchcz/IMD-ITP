// This program receives 1 integer number n, then it receives
// 2 integers numbers x and y and prints the sum of all odd
// numbers between x and y. This happens n times. 

#include <stdio.h>

int main()
{

    int n;

    scanf("%d", &n);

    for(int i = 0; i < n; i++)
    {
        int x, y;
        int sum = 0;
        scanf("%d", &x);
        scanf("%d", &y);
        y--;

        while(y > x)
        {
            if(y%2 != 0) sum += y;
            y--;
        }

        printf("%d \n", sum);
        sum = 0;
    }

    return 0;
}
