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
    
    ll num = 0, den = 1; 
    ll a, b;
    
    for(int i = 0; i < n; i++) {
        scanf("%lld/%lld", &a, &b);
        add_fraction(&num, &den, a, b);
    }
    
    reduce_fraction(&num, &den);
    
    ll integer = num / den;
    num = num % den;
    
    if(num < 0) { 
        num = -num;
        integer--;
    }
    
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
