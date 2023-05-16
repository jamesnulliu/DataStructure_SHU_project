#include <iostream>
#include "OrthogonalList.h"
using namespace std;

int main()
{
    try {
        system("color F0");
        char es[4] = { 'a','b','c','d' };
        int v = 0;
        orthogonal::Graph<char, int> g(es, 4);
        g.InsertArc(0, 1, 5);
        g.InsertArc(1, 2, 3);
        g.InsertArc(0, 3, 4);
        g.InsertArc(3, 2, 1);
        g.Display();
        g.DeleteVertex('b');

        cout << "------" << endl;;
        g.Display();
        int result[4] = { 0 };
        g.topologicalSorting(result);
        for (int i = 1; i < 5; i++)
        {
            for (int j = 0; j < 4; j++)
                if (result[j] == i) {
                    cout << g.GetElem(j) << "---";
                }
        }
        cout << endl;
    } catch (Error err)
    {
        err.Show();
    }
    system("pause");
}