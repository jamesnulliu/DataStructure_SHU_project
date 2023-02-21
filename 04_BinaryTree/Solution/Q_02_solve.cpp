#include "Solution.h"

//简单的递归函数
void Derive(int a,int b,int &leftStep,int &rightStep) {
    if (a==b&&a==1)//成功返回根节点判断
    {
        return;
    }
    else if (a<1||b<1)//无法返回根节点判断
    {
        leftStep=-1;
        rightStep=leftStep;
        return;
    }
    //计算上一级节点
    int temp=a;
    a=a<b?a:(a-b+(++leftStep)-leftStep);   
    b=b<temp?b:(b-temp+(++rightStep)-rightStep);
    Derive(a,b,leftStep,rightStep);
}
//改进后的版本
void Derive_improve(int a,int b,int &leftStep,int &rightStep) {
    //当递归到边缘节点时，会过度回溯。
    if (a==0)
    {
        leftStep-=1;
        return;
    }
    else if (b==0)
    {
        rightStep-=1;
        return;
    }
    //下面通过取模运算来优化递归，跳过连续经过同一方向节点的情况
    if (a>b)
    {
        leftStep+=a/b;
        a=a%b;
    }
    else {
        rightStep+=b/a;
        b=b%a;
    }
    Derive_improve(a,b,leftStep,rightStep);
}

void Q_02_refresh() {
    system("cls");
}

void Q_02_solve() {
    
}