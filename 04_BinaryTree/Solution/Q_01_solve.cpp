#include "Solution.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

struct node
{
    int data;
    node* left;
    node* right;
};

void write1(node* root, vector<int>& vec, int& i)
{
    if (vec[i] == '#') {
        delete root;
        return;
    }
    root->data = vec[i];
    root->left = new node;
    root->right = new node;
    write1(root->left, vec, ++i);
    write1(root->right, vec, ++i);
}

int i = 0;

void write(node* root, vector<int>& vec)
{
    if (vec[i] == '#') {
        delete root;
        return;
    }
    root->data = vec[i];
    ++i;
    int a = i;
    if (vec[a + 1] != '#') {
        root->left = new node;
        write(root->left, vec);
    }
    ++i;
    if (vec[a + 2] != '#') {
        root->right = new node;
        write(root->right, vec);
    }
}

node* root = new node;
void Q_01_refresh()
{
    system("cls");
    string str;
    cout << "Please input the tree: ";
    vector<int> vec;
    while (cin.good()) {
        int data; cin >> data;
        vec.push_back(data);
    }
    write(root, vec);
}

void reverse(node* root)
{
    if (root->left && root->right == nullptr)
        return;
    reverse(root->left);
    reverse(root->right);
    node* t = root->left;
    root->left = root->right;
    root->right = t;
}

void Q_01_solve()
{
    reverse(root);
}