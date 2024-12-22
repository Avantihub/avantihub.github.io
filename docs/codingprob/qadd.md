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

## WA_Solution

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
## TA version

```c

/*
Created by DoBetter in 20241211
Brief:
	7-9 N个数求和
*/


#include<stdio.h>
#include<math.h>
#define MAX 100

/*
Hint 

1.如果在输入时进行了约分，不需要使用long类型 
2.对负数的情况处理，gcd时，对绝对值进行gcd求解，以避免负号错位（如本来在分子位置变为分母）。 
3.注意gcd算法的正确性，大家容易漏条件，辗转相除法递归形式容易理解和避免条件泄露。
4.可以把debug的注释部分解开，自己本地去输出看看中间结果是否符合预期。

个人对测试点的猜测，欢迎补充和改进:
测试点0: 样例1
测试点1: 样例2，为1个整数输出 
测试点2,3: 存在负数，但对负数处理错误（比如负号错位） 
测试点4：类似于样例2，结果为1个整数输出，但不同于样例2
测试点5: 分子为0，此时如果gcd算法没有处理好，则会导致除0，产生浮点错误 

*/


// 最大公约数，辗转相除算法，递归形式。推荐学习
// int gcd(int a,int b){ 
//     return b==0?a:gcd(b,a%b);
// }

// 最大公约数，辗转相除算法，循环形式 
int gcd(int a,int b){ //没有对 

    if (a<b)
    {
        int temp=a;
        a=b;
        b=temp;
    }
    
    if(b==0){ //避免小的为0 
        return a;
    }
    
    while (a%b!=0)
    {
        int temp=a%b;
        a=b;
        b=temp;
    }
    return b;
    
}

// 最小公倍数
int lcm(int a,int b){
    return a*b/gcd(a,b);
}

int main(){
	
    int N,i,fz,fm,fz_arr[MAX],fm_arr[MAX];
    
    //输入并先约分
    scanf("%d",&N);
    for(i=0;i<N;i++){ 
        scanf("%d/%d",&fz,&fm);
        int g=gcd(abs(fz),abs(fm));
        fz/=g;
        fm/=g;
        fz_arr[i]=fz;
        fm_arr[i]=fm;
    }
    
     // for debug 输出约分后的所有分子分母 
//     for(i=0;i<N;i++){
//         printf("%d/%d ",fz_arr[i],fm_arr[i]);
//     }
//     printf("\n"); 

    // 求所有有理数的最小公倍数
    int fm_lcm = fm_arr[0];
    for(i=1;i<N;i++){
        fm_lcm = lcm(fm_lcm,fm_arr[i]);
    }

    // 求和
    int fz_sum=0;
    for(i=0;i<N;i++){
        fz_sum+=fz_arr[i]*fm_lcm/fm_arr[i];
    }
    
    // for debug 输出通分后的结果
//    printf("%d/%d\n",fz_sum,fm_lcm);
	
	if(fz_sum==0){ // 分子为0，不需要进行约分，直接输出 
		printf("0\n");
		return 0;
	}
	
    // 对最终相加结果约分    
    int g=gcd(abs(fz_sum),abs(fm_lcm));
    fz_sum/=g;
    fm_lcm/=g;
    
    int int_part = fz_sum/fm_lcm; //整数部分 
    if(int_part!=0){ //整数部分不为0 
    	printf("%d",int_part);
	}
	if(fz%fm_lcm){ //分子不为0 
		if(int_part!=0) printf(" ");
		printf("%d/%d",fz_sum%fm_lcm,fm_lcm); //分数部分 
	}

    return 0;
}

```

## Correct

```c

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define N 110

int gcd(int a,int b)
{
    if(a<b)
    {
        int t=a;
        a=b;
        b=t;
    }
    while (b) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int lcm(int a,int b)
{
    return (long long)a / gcd(a,b) * b;
}

int fz[N],fm[N];
int main()
{
    int n,i,x,y;
    scanf("%d",&n);
    
    scanf("%d/%d",&fz[0],&fm[0]);
    int g = gcd(abs(fz[0]), abs(fm[0]));
    fz[0] /= g;
    fm[0] /= g;
    
    int sum_fz = fz[0];
    int sum_fm = fm[0];
    
    for(i=1; i<n; i++) {
        scanf("%d/%d",&x,&y);
        g = gcd(abs(x), abs(y));
        x /= g;
        y /= g;
        
        int new_fm = lcm(sum_fm, y);
        sum_fz = sum_fz * (new_fm/sum_fm) + x * (new_fm/y);
        sum_fm = new_fm;
        
        g = gcd(abs(sum_fz), sum_fm);
        sum_fz /= g;
        sum_fm /= g;
    }
    if(sum_fz==0)
    {
        printf("0\n");
        return 0;
    }
    
    int inte = sum_fz/sum_fm;
    int remain = sum_fz%sum_fm;
    
    if(inte == 0)
        printf("%d/%d\n", remain, sum_fm);
    else if(remain == 0)
        printf("%d\n", inte);
    else
        printf("%d %d/%d\n", inte, remain, sum_fm);
        
    return 0;
}


``` 
```c
if(sum_fz==0)
    {
        printf("0\n");
        return 0;
    }
```

我来解释为什么这个判断很重要，并给出一个具体的测试数据。

这个判断是用来处理分数和为0的特殊情况。如果去掉这个判断，当sum_fz（分子）为0时，会继续执行后面的代码：

```c
int inte = sum_fz/sum_fm;    // 当 sum_fz 为0时，inte = 0
int remain = sum_fz%sum_fm;  // 当 sum_fz 为0时，remain = 0
```

虽然计算结果正确（inte = 0, remain = 0），但程序会继续到最后的输出判断部分：

```c
if(inte == 0)
    printf("%d/%d\n", remain, sum_fm);  // 会输出 "0/x" 的形式
else if(remain == 0)
    printf("%d\n", inte);
else
    printf("%d %d/%d\n", inte, remain, sum_fm);
```

这样会导致输出格式错误。比如对于以下测试数据：

```
2
1/2
-1/2
```

正确输出应该是：
```
0
```

但如果去掉那个判断，输出会变成：
```
0/1
```

这两种输出在数学上是等价的，但在这道题目的要求中，当结果为0时，应该直接输出"0"而不是"0/1"的分数形式。这就是为什么需要这个特殊判断的原因。
