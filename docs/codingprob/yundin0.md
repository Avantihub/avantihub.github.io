# 泉山顶云

## 题目描述

泉山顶云是一种细胞培养液，根据规定，其有效期为 $2$ 年 $6$ 个月。

现在告诉你一批泉山顶云的生产日期，以及今天的日期，请你回答其中有多少泉山顶云已经超过有效期，以及生产日期最早的泉山顶云的生产日期。

年和月简单后推计算，不考虑每个月具体天数。 $2016$ 年 $10$ 月 $5$ 日生产的泉山顶云，在 $2019$ 年 $4$ 月 $5$ 日当天仍然有效，从 $2019$ 年 $4$ 月 $6$ 日起失效。

## 输入格式

第一行为今天的日期。

第二行一个正整数 $n$ ，表示这批泉山顶云的数量。

随后 $n$ 行，每行一个日期，表示该泉山顶云的生产日期。

日期以这样的格式给出： `yyyy-mm-dd` ，表示 `年-月-日` 。

## 输出格式

第一行一个整数，表示已经超过有效期的泉山顶云的数量。

第二行一个日期，表示生产日期最早的泉山顶云的生产日期。

日期的输出格式应当与输入格式一致。

## 样例 #1

### 样例输入 #1

```
2024-11-26
5
2024-09-30
2022-05-26
2022-05-25
2022-05-27
2008-11-01
```

### 样例输出 #1

```
2
2008-11-01
```

## 提示

$ 1 \leq n \leq 1000 $

年份均为 $21$ 世纪年份。

## 考后重构思路

- 1. 日期比较，直接比较字符串即可，不需要转换为日期对象。
- 注意到题干中**年和月简单后推计算，不考虑每个月具体天数**
    - 考场上用特判处理"是否跨年"的情况，越写越多，增加bug的可能性
    - e.g. 2021.09-2024.03跨年，可以
    - 可以直接将年分转化为月份，然后直接比较月份即可
    - M=12*(year2-year1)+month2-month1
    - 日期的状态简化为是否超出day0,True or False

# After Reading Standard Solution

- Bacause the present date is fixed,we can calc the exact date when the product is out of date.
- it's easier than my sol:every time a new time comes,subtracted...be confusing
- just make a cmp func,for every date,compare with the expedited date

- **SUM: Make good use of the fixed date,make the problem easier**

## Standard Solution

```c
#include<stdio.h>

int n,y[1005],m[1005],d[1005],yy,mm,dd;
int cmp(int y1,int m1,int d1,int y2,int m2,int d2)
{
	//if 1 earlier than 2 return 1,else 0
	if(y1!=y2)return y1<y2;
	if(m1!=m2)return m1<m2;
	return d1<d2; 
} 
int main()
{
	scanf("%d-%d-%d",&yy,&mm,&dd);
	yy-=2;
    mm-=6;
	if(mm<=0)
	{
		yy--;
        mm+=12;
	}//calc outdated time
	scanf("%d",&n);
	int minn=1,ans=0;
	for(int i=1;i<=n;i++)
    {
		scanf("%d-%d-%d",&y[i],&m[i],&d[i]);
		if(cmp(y[i],m[i],d[i],y[minn],m[minn],d[minn]))minn=i;//record earliest time 
		if(cmp(y[i],m[i],d[i],yy,mm,dd))ans++;//lost date
	}
	printf("%d\n%d-%02d-%02d",ans,y[minn],m[minn],d[minn]);//formated output 
	return 0;
}
```