#include <iostream>
#include <math.h>
#include <cstdio>
using namespace std;
int main()

{
    std::puts("enter three digits in order to get solution of quodratic eqution");
    float a = 0;
    float b = 0;
    float c = 0;
    std::scanf("%f %f %f", &a, &b, &c);
    float x1 = (-b + sqrt(pow(b, 2) - 4 * a * c)) / 2 * a;
    float x2 = (-b - sqrt(pow(b, 2) - 4 * a * c)) / 2 * a;

    if ((b * b - 4 * a * c) >= 0)
    {
        std::printf("solution: %f %f\n", x1, x2);
    }
    else
    {
        std::printf("Discriminant less than 0");
    }
    system("pause");
    return 0;
}
