exp1 - Sample Input/Output
==========================

## p1/p2 - Student-Professor Problem

### 输入
* 多组数据输入。
* 每一组数据第一行四个正整数`p`、`n`、`m`、`t`，分别表示待安排的会面个数，学生总数，教授总数，时间点总数。
* 接下来`p`行每行三个正整数`u`、`v`、`w`，表示学生`u`想在时间点`w`和教授`v`会面。

### 输出
* 每组数据输出一行一个整数`x`，表示可安排的最大会面个数。

### 提示
* `p <= 10000`
* `n <= 100`
* `m <= 20`
* `t <= 30`
* 输入所给的教授、学生、时间点的编号均从1开始（和题目描述相同）。
* 所有教授在时间点`1 ~ t`都有空闲（即无视原题目描述中的Tj）。
* 两种情况的输入文件共用。

### 运行时间参考 - 不考虑一个学生最多只能见同一个教授一次（原题要求a、b、c）
##### Bipartite Graph Matching / Hungarian
`[in-big.txt > p1-out-big.txt] real    0m0.203s`  
##### Maximum Flow / ISAP
`[in-big.txt > p1-out-big.txt] real    0m0.189s`  

### 运行时间参考 - 一个学生最多只能见同一个教授一次（原题要求a、b、c、d）
##### Maximum Flow / ISAP
`[in-big.txt > p2-out-big.txt] real    0m0.218s`  

## 备注
* 以上所有程序均使用GCC 7.2.1编译，命令行为`g++ -o (exe) (src) -O2 -std=c++17 -Wall -Wconversion -Wextra -Wformat -Wsign-conversion -pedantic`。
* 运行时间使用UNIX time命令测量，命令行为`time ./(exe) < (input) > (output)`。
