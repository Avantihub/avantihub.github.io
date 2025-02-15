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

图中从左到右依次为AND OR NOT门

## Vector

```verilog
wire [99:0] my_vector;      // Declare a 100-element vector
assign out = my_vector[10]; // Part-select one bit out of the vector
```

```verilog

module example;
    wire [0:7] b;  // 定义一个8位宽的wire变量b,位宽定义中的 0 和 7 分别表示最低位（LSB）和最高位（MSB）。

    assign b = 8'b11001100;  // 给b赋值

    initial begin
        $display("b = %b", b);  // 输出b的值：11001100
        $display("b[0] = %b", b[0]);  // 输出b的第0位：0
        $display("b[7] = %b", b[7]);  // 输出b的第7位：1
    end
endmodule

```
### endianness 大端小端规则("direction")

- LSB在低位，MSB在高位，称为小端（little-endian）e.g., [3:0]
- LSB在高位，MSB在低位，称为大端（big-endian）e.g., [0:3]

### Implicit nets隐式线网导致错误

- 未声明直接使用：通过assign语句或未声明模块端口引用时，Verilog会自动创建1位宽wire类型的隐式线网
- 解决：禁用隐式机制，使用`default_nettype none编译指令强制显式声明

```verilog
// Implicit nets

`default_nettype none//强制显式声明

wire [2:0] a, c;   // Two vectors
assign a = 3'b101;  // a = 101
assign b = a;       // b =   1  implicitly-created wire
assign c = b;       // c = 001  <-- bug
my_module i1 (d,e); // d and e are implicitly one-bit wide if not declared.
                    // This could be a bug if the port was intended to be a vector.
```

### Unpacked array

```verilog
reg [7:0] mem [255:0];   // 256 unpacked elements, each of which is a 8-bit packed vector of reg.
reg mem2 [28:0];         // 29 unpacked elements, each of which is a 1-bit reg.
```

### 取用vector元素：Part-Select

如果左右vector的位宽不同，会自动进行zero-extension或truncated截断

```verilog
wire [7:0] w;
w[3:0]      // Only the lower 4 bits of w
w[7:4]      // Only the upper 4 bits of w
```
### 接短成长Concatenation

```verilog
{3'b111, 3'b000} => 6'b111000
{1'b1, 1'b0, 3'b101} => 5'b10101
{4'ha, 4'd10} => 8'b10101010     // 4'ha and 4'd10 are both 4'b1010 in binary
```
## 里外module

You are given the following module:

module mod_a ( output out1, output out2, input in1, input in2, input in3, input in4);

![modules](/home/avanti/.local/mkdocs-site/docs/assets/images/cs/modn.png)

```verilog


module top_module ( 
    input a, 
    input b, 
    input c,
    input d,
    output out1,
    output out2
);
    mod_a ins(
        .out1(out1),
        .out2(out2),
        .in1(a),//.in1(a)表示将a连接到in1,in1是里面的mod_a的输入, a是外面的top_module的输入
        .in2(b),
        .in3(c),
        .in4(d)
    );

endmodule
```