!!! info
    本文档是对于Verilog的学习笔记，主要参考了[Verilog教程](https://www.runoob.com/verilog/verilog-tutorial.html)。
    [HDLbits](https://hdlbits.01xz.net/wiki/Main_Page)是一个很好的练习网站。
    [答案链接](https://blog.csdn.net/wangkai_2019/article/details/106664283)


## 表示整数

格式：`[size位宽]'[base进制]value数字`

counter = 'd100 ; //一般会根据编译器自动分频位宽，常见的为32bit，10进制100
counter = 100 ;
counter = 32'h64 ;32位宽，16进制6*16+4=100

## 表示浮点数

!!! info
    30.123 
    1.2e4         //大小为12000
    1_0001e4      //大小为100010000
    1E-3          //大小为0.001

## 字符串表示方法
字符串是由双引号包起来的字符队列。字符串不能多行书写，即字符串中不能包含回车符。Verilog 将字符串当做一系列的单字节 ASCII 字符队列。例如，为存储字符串 "www.runoob.com", 需要 14*8bit 的存储单元。例如：

```verilog
reg [0: 14*8-1]       str ;
initial begin
    str = "www.runoob.com";
end
```

## Wire

verilog里的wire是有向边，从source到sink，是一个连接。
源：source，driver，驱动器
汇：sink，load，负载器

continuous assign: 在assign l=r中，r的值改变，l的值也会改变
(与编程语言不同，assign语句描述connection而非action)

XNOR: 异或非门，ans=~(a^b),相同为1，不同为0

![logic gates](/home/avanti/.local/mkdocs-site/docs/assets/images/cs/andg.png)