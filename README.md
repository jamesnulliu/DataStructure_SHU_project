# DataStructure_SHU_project

## Basic Information

This is a set of data structure course project of Shanghai University, given by 朱能军.

The authors of the origin project are JamesNULLiu, Lrf8182, Pedestrian0626

All the codes are fully C++ and under the standard of **C++20**.

This project is based on Apache-2.0 License.

According to this license, you can use the involved codes for free.

But you **MUST** **NOT** fully copy the project and make it as your own course project.

You **MUST** add a completely same and intact copy of the file [LICENSE](https://github.com/jamesnulliu/SHU_DS_znj_Project01/blob/main/LICENSE) to your project if you are using relevant codes.

## Poject 01

Project 01 is to solve 2 following questions:

### 一、面试安排（1）

1. 问题描述
    某IT公司招聘新员工，已收到N份简历，人力资源部X和Y负责挑选简历安排面试。他们把N份简历排成一个圆圈，按逆时针方向编号为1～N。开始时X站在1号简历前，按逆时针方向数到第K份简历，选中；Y站在N号简历前，按顺时针方向数到第M份简历，选中。两人同时取走所选简历后，分别按逆时针和顺时针走到下一份简历前，然后X和Y再重复上述方法取简历，直到取走全部简历，如果两人选中同一份简历，则只输出一个编号。

2. 基本要求
    要求输入3个数N、K和M，按取走简历的顺序（先甲后已）输出简历编号。

3. 测试数据
    输入样例：10 4 3
    输出样例：4, 8; 9, 5; 3, 1; 2, 6; 10; 7

### 二、面试安排（2）

1. 问题描述
    某IT公司招聘新员工，已收到N份简历，人力资源部X和Y负责挑选简历安排面试，Z负责补充新的简历。他们把N份简历排成一个圆圈，按逆时针方向编号为1～N。开始时X站在1号简历前，按逆时针方向数到第K份简历，选中；Y站在N号简历前，按顺时针方向数到第M份简历，选中。两人同时取走所选简历后，分别按逆时针和顺时针走到下一份简历前，每到此时（除非所有简历都已取完），Z都会拿来1份新简历（编号从N+1开始递加），插到X前面，然后X和Y再重复上述方法取简历，直到取走全部简历，如果两人选中同一份简历，则只输出一个编号。

2. 基本要求
    要求输入3个数N、K和M，按取走简历的顺序（先甲后已）输出简历编号。

3. 测试数据
    输入样例：5 1 1
    输出样例：1, 5; 6, 4; 7, 3; 8, 2

## Project 02

Project 02 is to solve 2 following questions:

### 一、车厢调度（1）

1. 问题描述
有一个“丁”字型铁路调度系统如图1所示，它由相互垂直的2条铁轨组成，水平方向的为主铁轨，竖直方向的为辅助铁轨。辅助铁轨用于对车厢次序进行调整，它在主铁轨中间，把主铁轨分成左右两个部分。主铁轨左边的车厢只能从左边开到右边，或者从主铁轨左边进入辅助铁轨；辅助铁轨上的车厢只可以进入主铁轨右边。
现在有n节火车车厢，编号为1、2、...、n，在主铁轨的左边按顺序驶入，要求通过这个调度系统，在主铁轨的右边以指定次序开出（例如：有5节车厢以1、2、3、4、5 的次序进入，要求以3、2、5、4、1的顺序出站)。请编程求解调度过程。

2. 输入数据
输入共2行，第1行一个正整数n表示车厢数目；第2行是1-n的任意排列，表示n节车厢在主铁轨右边的排列顺序。

3. 输出数据
    如果能完成调度，则输出调度过程，否则输出调度失败信息。

### 二、车厢调度（2）

1. 问题描述
有一个“丁”字型铁路调度系统如图2所示，它由相互垂直的2条铁轨组成，水平方向的为主铁轨，竖直方向的为辅助铁轨。辅助铁轨用于对车厢次序进行调整，它在主铁轨中间，把主铁轨分成左右两个部分。主铁轨左边的车厢只能从左边开到右边，或者从主铁轨左边进入辅助铁轨；辅助铁轨上的车厢只可以进入主铁轨右边。
现在有n节火车车厢，编号为1、2、...、n，在主铁轨的左边以任意的顺序驶入，要求通过这个调度系统，在主铁轨的右边以1、2、...、n的次序开出（例如：有5节车厢以 5、3、1、2、4 的次序进入，要求以1、2、3、4、5的顺序出站)。请编程求解调度过程。

2. 输入数据
输入共2行，第1行一个正整数n表示车厢数目；第2行是1-n的任意排列，表示n节车厢在主铁轨左边的排列顺序。

3. 输出数据
如果能完成调度，则输出调度过程，否则输出调度失败信息。