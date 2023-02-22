#include "Solution.h"
#include <string>
#include <iostream>
using namespace std;

struct node
{
    int data;
    node *left;
    node *right;
};

void write1(node *root, string &str, int &i)
{
    if(str[i]=='#'){
        delete root;
        return;
    }
    root->data=str[i];
    root->left=new node;
    root->right=new node;
    write1(root->left,str,++i);
    write1(root->right,str,++i);
}

int i = 0;

void write(node *root, string &str)
{

    if (str[i] == '#')
    {
        delete root;
        return;
    }
    root->data = str[i];
    ++i;
    if (str[i + 1] != '#')
    {
        root->left = new node;
        write(root->left, str);
    }
    ++i;
    if (str[i + 2] != '#')
    {
        root->right = new node;
        write(root->right, str);
    }
}

node *root = new node;
void Q_01_refresh()
{
    system("cls");
    string str;
    cout << "Please input the tree: ";
    cin >> str;
    write(root, str);
}

void reverse(node *root)
{
    if (root->left && root->right == nullptr)
        return;
    reverse(root->left);
    reverse(root->right);
    node *t = root->left;
    root->left = root->right;
    root->right = t;
}

void Q_01_solve()
{
    reverse(root);
}