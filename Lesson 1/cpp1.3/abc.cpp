#include <cstdio>
#include <iostream>
using namespace std;
int main()
{
    int a = 0;
    int b = 0;
    int c = 0;
    std::puts("enter three digit in order to get sum of these three digits ");
    std::scanf("%d %d %d", &a, &b, &c);

    int y = a + b + c;

    std::printf("%d + %d + %d = %d\n", a, b, c, y);

    system("pause");
    return 0;
}
