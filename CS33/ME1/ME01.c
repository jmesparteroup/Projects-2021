#include<stdio.h>
#include<math.h>
#define newline printf("\n")

int main ()
{
    newline;
    printf("HI");
    newline;
    newline;

    printf("CCCCCCC");
    newline;
    printf("C     C");
    newline;
    printf("C     C");
    newline;
    newline;

    printf("LLLLLLL");
    newline;
    printf("L");
    newline;
    printf("L");
    newline;
    newline;

    printf("S  SSSS");
    newline;
    printf("S  S  S");
    newline;
    printf("SSSS  S");
    newline;
    

    int time, hr, min, sec; 
    double deg, mins, secs, rad;

    newline;
    printf("Enter time in seconds: ");
    scanf("%d", &time);

    hr = floor(time/3600);
    min = floor((time - 3600*hr)/60);
    sec = time - 3600*hr - 60*min;

    printf("%02d hours, %02d minutes, and %02d seconds", hr, min, sec);

    newline;
    newline;
    printf("Enter an angle in DDD*MM\'SS.SSS\": ");
    scanf("%lf%*c%lf%*c%lf", &deg, &mins, &secs);

    rad = M_PI * (deg + mins/60 + secs/3600)/180;

    printf("Result: %09f", rad);
    newline;
    newline;

    return 0;
}

//15555*42’27”