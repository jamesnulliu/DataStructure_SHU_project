# DataStructure_SHU_project

## Basic Information

This is a set of data structure course project of Shanghai University, given by 朱能军.

The authors of the origin project are JamesNULLiu, Lrf8182, Pedestrian0626

All the codes are fully C++ and under the standard of **C++20**.

This project is based on Apache-2.0 License.

According to this license, you can use the involved codes for free.

But you **MUST** **NOT** fully copy the project and make it as your own course project.

You **MUST** add a completely same and intact copy of the file [LICENSE](https://github.com/jamesnulliu/SHU_DS_znj_Project01/blob/main/LICENSE) to your project if you are using relevant codes.

**Check [*Proj01_Report.pdf*](https://github.com/jamesnulliu/SHU_DS_znj_Project01/blob/main/report/Proj01_Report.pdf) for more information about this project.**

## Poject 01

Project 01 is to solve 2 following questions:

### 一、面试安排（1）

1、问题描述
某IT公司招聘新员工，已收到N份简历，人力资源部X和Y负责挑选简历安排面试。他们把N份简历排成一个圆圈，按逆时针方向编号为1～N。开始时X站在1号简历前，按逆时针方向数到第K份简历，选中；Y站在N号简历前，按顺时针方向数到第M份简历，选中。两人同时取走所选简历后，分别按逆时针和顺时针走到下一份简历前，然后X和Y再重复上述方法取简历，直到取走全部简历，如果两人选中同一份简历，则只输出一个编号。

2、基本要求
要求输入3个数N、K和M，按取走简历的顺序（先甲后已）输出简历编号。

3、测试数据
输入样例：10 4 3
输出样例：4, 8; 9, 5; 3, 1; 2, 6; 10; 7

### 二、面试安排（2）

1、问题描述
某IT公司招聘新员工，已收到N份简历，人力资源部X和Y负责挑选简历安排面试，Z负责补充新的简历。他们把N份简历排成一个圆圈，按逆时针方向编号为1～N。开始时X站在1号简历前，按逆时针方向数到第K份简历，选中；Y站在N号简历前，按顺时针方向数到第M份简历，选中。两人同时取走所选简历后，分别按逆时针和顺时针走到下一份简历前，每到此时（除非所有简历都已取完），Z都会拿来1份新简历（编号从N+1开始递加），插到X前面，然后X和Y再重复上述方法取简历，直到取走全部简历，如果两人选中同一份简历，则只输出一个编号。

2、基本要求
要求输入3个数N、K和M，按取走简历的顺序（先甲后已）输出简历编号。

3、测试数据
输入样例：5 1 1
输出样例：1, 5; 6, 4; 7, 3; 8, 2

## Project 02

Project 02 is to solve 2 following questions: