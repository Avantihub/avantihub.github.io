#include <stdio.h>

struct student
{
    char a[3];
    char b[20];
    char c;
    double d;
    char e;
};

int main()
{
    struct student stu;
    int a, b;

    stu.a[0] = 'A', stu.a[1] = 'B', stu.a[2] = 'C';
    for (int i = 0; i < 20;i++)
        stu.b[i] = i;
    stu.c = '0';
    stu.d = 16.0;
    stu.e = 'a';

    

    return 0;
}