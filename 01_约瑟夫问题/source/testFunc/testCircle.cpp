#include "../../header/testFunc/testArrayList.h"
#include "../../header/linkedList/dChain_circle.h"
#include "../../header/linkedList/dNode.h"
#include <sstream>

using namespace std;

template<class T>
using circle = dChain_circle<T>;

void Move(dNode<int>** p, int step) //The point move by X steps
{
    if (step >= 0) {
        for (int i = 0; i < step; i++) {
            *p = (*p)->next;
        }
    } else if (step < 0) {
        for (int i = 0; i < -step; i++) {
            *p = (*p)->prev;
        }
    }
}

void Erase(dNode<int>* p)  //Delete the node pointed by p;
{
    dNode<int>* t;
    t = p;
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
}

void circle_test1(int N, const int k, const int m, std::ostream* out)
{
    std::ostream& Out = *out;
    std::ostringstream outputString;
    circle<int> chain;
    for (int i = 0; i < N; i++)
    {
        chain.insert(i, i + 1);
    }
    dNode<int>* px = chain.get_firstNode();
    dNode<int>* py = chain.get_lastNode();
    int nResume = N;
    while (nResume != 0)
    {
        // Calculate {stepX} and {stepY} @{
        int stepX = k % nResume - 1;
        int stepY = -(m % nResume - 1);
        if (stepX > (nResume / 2)) { stepX = stepX - nResume; }
        if (-stepY > (nResume / 2)) { stepY = nResume + stepY; }
        // @}
        Move(&px, stepX);
        Move(&py, stepY);
        int data_x = px->element;
        int data_y = py->element;
        dNode<int>* temp_x = px;
        dNode<int>* temp_y = py;
        if (px->next == py) {
            Move(&px, 2);
            Move(&py, -2);
        } else {
            Move(&px, 1);
            Move(&py, -1);
        }
        if (temp_x == temp_y) {
            chain.erase(temp_x);
            nResume--;
        } else {
            chain.erase(temp_x);
            chain.erase(temp_y);
            nResume -= 2;
        }
        if ((data_x == data_y) && (nResume != 0)) {
            outputString << data_x << "; ";
        } else if ((data_x == data_y) && (nResume == 0)) {
            outputString << data_x;
        } else if ((data_x != data_y) && (nResume != 0)) {
            outputString << data_x << ", " << data_y << "; ";
        } else if ((data_x != data_y) && (nResume == 0)) {
            outputString << data_x << ", " << data_y;
        }
    }
    if (out != nullptr) {
        (*out) << outputString.str() << std::endl;
    }
}

void circle_test2(int N, const int k, const int m, std::ostream* out)
{
    std::ostringstream outputString;
    circle<int> chain;
    for (int i = 0; i < N; i++) {
        chain.insert(i, i + 1);
    }
    dNode<int>* px = chain.get_firstNode();
    dNode<int>* py = chain.get_lastNode();
    int nResume = N, max = N;

    while (nResume != 0)
    {
        int stepX = k % nResume - 1;
        int stepY = -(m % nResume - 1);
        if (stepX > (nResume / 2)) { stepX = stepX - nResume; }
        if (-stepY > (nResume / 2)) { stepY = nResume + stepY; }
        Move(&px, stepX);
        Move(&py, stepY);
        int data_x = px->element;
        int data_y = py->element;
        dNode<int>* temp_x = px, * temp_y = py;
        bool flag = false;

        if (px->next == py) {
            Move(&px, 2);
            Move(&py, -2);
            flag = true;
        } else {
            Move(&px, 1);
            Move(&py, -1);
        }

        if (temp_x == temp_y) {
            // constraint
            if ((m + k) % nResume == 1) {
                outputString << " => endless loop";
                break;
            }
            chain.erase(temp_x);
            nResume--;
        } else {
            chain.erase(temp_x);
            nResume--;
            chain.erase(temp_y);
            nResume--;
        }
        if (nResume != 0) {
            chain.insert(px->prev, ++max);
            nResume++;
        }
        px = px->prev;
        if (flag) {
            py = py->next;
        }

        if ((data_x == data_y) && (nResume != 0)) {
            outputString << data_x << "; ";
        } else if ((data_x == data_y) && (nResume == 0)) {
            outputString << data_x;
        } else if ((data_x != data_y) && (nResume != 0)) {
            outputString << data_x << ", " << data_y << "; ";
        } else if ((data_x != data_y) && (nResume == 0)) {
            outputString << data_x << ", " << data_y;
        }
    }
    if (out != nullptr) {
        (*out) << outputString.str() << std::endl;
    }
}