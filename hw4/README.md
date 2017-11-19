hw4 - Sample Input/Output
=========================

## p1 - Matrix Chain Multiplication

### 输入
* 多组数据输入。
* 每一组数据第一行一个正整数`n`，表示矩阵个数。
* 接下来`n`行每行两个整数`r`和`c`，表示一个矩阵的行数和列数。

### 输出
* 每组数据输出一行`minimum scalar multiplications: W`，其中`W`为最少需要的标量乘法次数。
* 每组数据输出后空一行。

### 提示
* `n <= 400`
* `r, c <= 200000`
* 最终答案保证可被64位无符号整数表示。
* 输入中每两个相邻的矩阵保证前一个的列数等于后一个的行数。

### 运行时间参考 - p1.cpp
* `[p1-in-big.txt > p1-out-big.txt] real    0m0.051s`

## p2 - Sequence Alignment

### 输入
* 多组数据输入。
* 每一组数据第一行一个正整数`m`，表示字符集的大小。
* 接下来一行`m`个非负整数，其中第`i`个表示`δ(i)`。
* 接下来`m`行，每一行`m`个非负整数，其中第`i`行第`j`列表示`α(i, j)`，其中`i`为`s1`中某字符，`j`为`s2`中某字符。
* 接下来一行表示第一个字符串`s1`，首先一个正整数`n`表示长度，然后`n`个非负整数表示第一个字符串内容。
* 一组数据的最后一行表示第二个字符串`s2`，格式同上。

### 输出
* 每组数据输出一行`minimum penalties: W`，其中`W`为最小penalty。
* 每组数据输出后空一行。

### 提示
* `m <= 64`
* `n <= 10000`
* `δ(i), α(i, j) <= 20000`
* 最终答案保证可被32位无符号整数表示。
* 相对原题目，这里使用了非负整数来代替字符。
* 上述`i`和`j`均从0开始计数，即满足`0 <= i, j < m`。
* 对于给定`i`和`j`，不保证`α(i, j) = α(j, i)`。
* 不保证各`δ(i)`和各`α(i, j)`之间的大小关系。
* 强烈不建议使用最短路算法使用`p2-in-huge.txt`。


### 运行时间参考（动态规划） - p2-dp.cpp
* `[p2-in-big.txt > p1-out-big.txt] real    0m0.042s`
* `[p2-in-huge.txt > p1-out-huge.txt] real    0m2.043s`

### 运行时间参考（最短路） - p2-sp.cpp
* `[p2-in-big.txt > p1-out-big.txt] real    0m4.157s`
* 不使用`p2-in-huge.txt`。

## 备注
* 以上所有程序均使用GCC 7.2.1编译，命令行为`g++ -o (exe) (src) -O2 -std=c++17 -Wall -Wconversion -Wextra -Wformat -Wsign-conversion -pedantic`。
* 运行时间使用UNIX time命令测量，命令行为`time ./(exe) < (input) > (output)`。
