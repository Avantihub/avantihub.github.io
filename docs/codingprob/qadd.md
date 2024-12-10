## Problem Description
本题的要求很简单，就是求N个数字的和。麻烦的是，这些数字是以有理数分子/分母的形式给出的，你输出的和也必须是有理数的形式。

## Input Format
输入第一行给出一个正整数N（≤100）。随后一行按格式a1/b1 a2/b2 ...给出N个有理数。题目保证所有分子和分母都在长整型范围内。另外，负数的符号一定出现在分子前面。

## Output Format
输出上述数字和的最简形式 —— 即将结果写成整数部分 分数部分，其中分数部分写成分子/分母，要求分子小于分母，且它们没有公因子。如果结果的整数部分为0，则只输出分数部分。

## Input Example 1

> 5

> 2/5 4/15 1/30 -2/60 8/3

## Output Example 1

> 3 1/3
## Input Example 2

> 2

> 4/3 2/3

## Output Example 2

> 2

## Input Example 3

> 3

> 1/3 -1/6 1/8

## Output Example 3

> 7/24

## Solution

```c

#include <stdio.h>
#include <stdlib.h>
#define ll long long

// 求最大公约数
ll gcd(ll a, ll b) {
    if(b == 0) return a;
    return gcd(b, a % b);
}

// 通分并相加
void add_fraction(ll *num, ll *den, ll a, ll b) {
    ll lcm = (*den / gcd(*den, b)) * b; // 最小公倍数
    *num = *num * (lcm / *den) + a * (lcm / b);
    *den = lcm;
}

// 化简分数
void reduce_fraction(ll *num, ll *den) {
    ll d = gcd(llabs(*num), llabs(*den));
    *num /= d;
    *den /= d;
    // 如果分母为负,将负号移到分子
    if(*den < 0) {
        *num = -*num;
        *den = -*den;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    
    ll num = 0, den = 1; // 结果分数的分子分母
    ll a, b;
    
    for(int i = 0; i < n; i++) {
        scanf("%lld/%lld", &a, &b);
        add_fraction(&num, &den, a, b);
    }
    
    reduce_fraction(&num, &den);
    
    // 提取整数部分
    ll integer = num / den;
    num = num % den;
    
    if(num < 0) { // 处理负数
        num = -num;
        integer--;
    }
    
    // 输出结果
    if(integer != 0) {
        printf("%lld", integer);
        if(num != 0) printf(" %lld/%lld", num, den);
    }
    else if(num != 0) {
        printf("%lld/%lld", num, den);
    }
    else {
        printf("0");
    }
    
    return 0;
}


``` 
## Sample

```c

#include <stdio.h>
long gcd(long n,long m) {
	if(n<0) n=-n;
	long g=m;
	while(n>0) {
		g=n;
		n=m%n;
		m=g;
	}
	return g;
}
int main() {
	long n,i,g;
	long a,b,aa,bb;
	scanf("%ld",&n);
	scanf("%ld/%ld",&aa,&bb);
	for(i=1; i<n; i++) {
		scanf("%ld/%ld",&a,&b);
		aa=aa*b+bb*a;
		bb=bb*b;
		g=gcd(aa,bb);
		aa=aa/g;
		bb=bb/g;
	}
	if(aa%bb==0)
		printf("%ld",aa/bb);
	else if(aa/bb==0)
		printf("%ld/%ld",aa%bb,bb);
	else
		printf("%ld %ld/%ld",aa/bb,aa%bb,bb);
	return 0;
}

```
