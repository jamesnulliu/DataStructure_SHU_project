#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <iterator>
#include "../linearList.h"
#include "../myExceptions.h"
#include "changeLength1D.h"

template<class T>
class arrayList : public linearList<T>
{
public:
    // constructor, copy constructor and destructor
    arrayList(int initialCapacity = 10);
    arrayList(const arrayList<T>&);
    ~arrayList() { delete element; }
    void clear();

    // @brief Return <true> if the list is empty, otherwise <false>.
    bool empty() const { return listSize == 0; }
    // @brief Return size of the list.
    int size() const { return listSize; }
    // @brief Get the element with index {theIndex}.
    T& get(int theIndex);
    // @brief Get the const element with index {theIndex}.
    const T& get(int theIndex) const;
    // @brief Get the element with its index.
    T& operator[](int index) { checkIndex(index); return element[index]; }
    // @brief Get the const element with its index.
    const T& operator[](int index) const { checkIndex(index); return element[index]; }
    // @brief Find and return the index with and element value; Return <-1> if not found.
    int indexOf(const T& theElement) const;
    // @brief Erase an element with index {theIndex}.
    void erase(int theIndex);
    /**
     * @brief Insert an element to location {theIndex}.
     * @param theIndex The index the inserted element would have after insertion.
    */
    void insert(int theIndex, const T& theElement);
    // @brief Push an element to the end of the list.
    void push_back(const T& theElement) { insert(listSize, theElement); }
    // @brief Output the list with a std::ostream object.
    void output(std::ostream& out) const;

    // @brief Return the capacity of the list.
    int capacity() const { return listCapacity; }
    // @brief Shrink the list to make each element appear only once. O(n2)
    void shrink_to_unique_On2();
    // @brief Shrink the list to make each element appear only once. O(n)
    void shrink_to_unique_On();
    // @brief Reverse the list.
    void reverse();

    // iterators to start and end of list
    class iterator;
    iterator begin() { return iterator(element); }
    iterator end() { return iterator(element + listSize); }

    // iterator for arrayList
    class iterator
    {
    public:
        // typedefs required by C++ for a bidirectional iterator
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T* pointer;
        typedef T& reference;

        // constructor
        iterator(T* thePosition = nullptr) { position = thePosition; }

        // dereferencing operators
        T& operator*() const { return *position; }
        T* operator->() const { return &*position; }

        // increment
        iterator& operator++() { ++position; return *this; }
        iterator operator++(int) { iterator old = *this; ++position; return old; }
        iterator operator+(difference_type offset) { return position + offset; }

        // decrement
        iterator& operator--() { --position; return *this; }
        iterator operator--(int) { iterator old = *this; --position; return old; }
        iterator operator-(difference_type offset) { return position - offset; }

        // equality testing
        bool operator!=(const iterator right) const { return position != right.position; }
        bool operator==(const iterator right) const { return position == right.position; }

    protected:
        T* position;
    };  // end of iterator class

protected:
    void checkIndex(int theIndex) const;
    T* element;            // 1D array to hold list elements
    int listCapacity;      // capacity of the 1D array
    int listSize;          // number of elements in list
};

template<class T>
arrayList<T>::arrayList(int initialCapacity)
{// Constructor.
    if (initialCapacity < 1)
    {
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(s.str());
    }
    listCapacity = initialCapacity;
    element = new T[listCapacity];
    listSize = 0;
}

template<class T>
arrayList<T>::arrayList(const arrayList<T>& theList)
{// Copy constructor.
    listCapacity = theList.listCapacity;
    listSize = theList.listSize;
    element = new T[listCapacity];
    std::copy(theList.element, theList.element + listSize, element);
}

template<class T>
void arrayList<T>::clear()
{
    delete element;
    listCapacity = 10;
    element = new T[listCapacity];
    listSize = 0;
}

template<class T>
void arrayList<T>::checkIndex(int theIndex) const
{// Verify that theIndex is between 0 and listSize - 1.
    if (theIndex < 0 || theIndex >= listSize)
    {
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }
}

template<class T>
T& arrayList<T>::get(int theIndex)
{
    checkIndex(theIndex);
    return element[theIndex];
}

template<class T>
const T& arrayList<T>::get(int theIndex) const
{
    checkIndex(theIndex);
    return element[theIndex];
}
template<class T>
int arrayList<T>::indexOf(const T& theElement) const
{// Return index of first occurrence of theElement.
 // Return -1 if theElement not in list.

   // search for theElement
    int theIndex = (int) (std::find(element, element + listSize, theElement) - element);

    // check if theElement was found
    if (theIndex == listSize) { return -1; } else { return theIndex; }
}

template<class T>
void arrayList<T>::erase(int theIndex)
{// Delete the element whose index is theIndex.
    checkIndex(theIndex);
    std::copy(element + theIndex + 1, element + listSize, element + theIndex);
    element[--listSize].~T();
}

template<class T>
void arrayList<T>::insert(int theIndex, const T& theElement)
{// Insert theElement so that its index is theIndex.
    if (theIndex < 0 || theIndex > listSize)
    {// invalid index
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }

    // valid index, make sure we have space
    if (listSize == listCapacity)
    {// no space, double capacity
        changeLength1D(element, listCapacity, 2 * listCapacity);
        listCapacity *= 2;
    }

    // shift elements right one position
    std::copy_backward(element + theIndex, element + listSize, element + listSize + 1);

    element[theIndex] = theElement;

    listSize++;
}

template<class T>
void arrayList<T>::output(std::ostream& out) const
{// Put the list into the stream out.
    std::copy(element, element + listSize, std::ostream_iterator<T>(out, "  "));
}

// overload <<
template <class T>
std::ostream& operator<<(std::ostream& out, const arrayList<T>& x)
{
    x.output(out);
    return out;
}

template <class T>
void arrayList<T>::shrink_to_unique_On2()
{
    // This method uses std::unordered_set, an efficient STL container whose implementation
    // is based on concept of hash map (the {VALUE} is omitted, leaving the {KEY}).
    // std::unordered_set shares the same efficiency with std::unordered_map (STL hash map).
    std::unordered_set<T> set;
    // Because I have designed {iterator} for class {arrayList}, most STL methods can be used
    // with {arrayList}. Therefor, following `for(...)` can be substituted for RANGE FOR (C++11),
    // i.e., `for(auto e: this){...}`.
    for (int i = 0; i < listSize;) {
        // If {element[i]} has not been added to {set}:
        if (set.count(element[i]) == 0) {
            // Add {element[i]} to {set}:
            set.emplace(element[i]);
            ++i;
        }
        // Else if {element[i]} has already been in {set}:
        else {
            // Erase the reduplicate element:
            erase(i);
            // After invoking method {erase()}, {listSize} will decrease automatically.
        }
    }
}

template<class T>
void arrayList<T>::shrink_to_unique_On()
{
    std::unordered_set<T> set;
    arrayList<T> temp;
    for (auto e : *this) {
        if (set.count(e) == 0) {
            set.emplace(e);
            temp.push_back(e);
        }
    }
    delete[] element;
    listSize = temp.size();
    listCapacity = temp.capacity();
    element = new T[listCapacity];
    std::copy(temp.begin(), temp.end(), this->begin());
}

template<class T>
void arrayList<T>::reverse()
{
    for (int i = 0; i <= listSize / 2; ++i) {
        std::swap(element[i], element[listSize - 1 - i]);
    }
}
