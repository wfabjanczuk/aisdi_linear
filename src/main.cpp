#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>
#include <chrono>

#include "Vector.h"
#include "LinkedList.h"

using namespace std;

#define prependLabel "PREPEND PERFORMANCE TEST"
#define popFirstLabel "POP FIRST PERFORMANCE TEST"
#define copyLabel "COPY PERFORMANCE TEST"

namespace
{

    template<typename T>
    using Vector = aisdi::Vector<T>;

    template<typename T>
    using LinkedList = aisdi::LinkedList<T>;

}

void VectorPrepend(Vector<int>& vector) {
    vector.prepend(1);
}

void ListPrepend(LinkedList<int>& list) {
    list.prepend(1);
}

void VectorPopFirst(Vector<int>& vector) {
    vector.popFirst();
}

void ListPopFirst(LinkedList<int>& list) {
    list.popFirst();
}

void VectorCopy(Vector<int>& vector) {
    Vector<int> new_vector;
    new_vector = vector;
}

void ListCopy(LinkedList<int>& list) {
    LinkedList<int> new_list;
    new_list = list;
}

void test(
        int collection_size,
        int repeat_count,
        string label,
        void (*vectorTest)(Vector<int>&),
        void (*listTest)(LinkedList<int>&)) {
    Vector<int> vector;
    LinkedList<int> list;

    for (int i = 0; i < collection_size; i++) {
        vector.append(i);
        list.append(i);
    }
    cout << "\n>> " << label << "\n\n";
    cout << "> Collection size N=" << collection_size << endl;
    cout << "> Repeat count k=" << repeat_count << endl;

    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < repeat_count; i++) {
        vectorTest(vector);
    }
    auto finish = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = finish - start;
    cout << "> Vector::prepend elapsed time: " << elapsed.count() << " s\n";

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < repeat_count; i++) {
        listTest(list);
    }
    finish = chrono::high_resolution_clock::now();
    elapsed = finish - start;
    cout << ">   List::prepend elapsed time: " << elapsed.count() << " s\n\n";
}

int main() {

    test(1000, 5, prependLabel, &VectorPrepend, &ListPrepend);
    test(10000, 5, prependLabel, &VectorPrepend, &ListPrepend);
    test(100000, 5, prependLabel, &VectorPrepend, &ListPrepend);
    test(1000000, 5, prependLabel, &VectorPrepend, &ListPrepend);
    test(10000000, 5, prependLabel, &VectorPrepend, &ListPrepend);

    test(1000, 5, popFirstLabel, &VectorPopFirst, &ListPopFirst);
    test(10000, 5, popFirstLabel, &VectorPopFirst, &ListPopFirst);
    test(100000, 5, popFirstLabel, &VectorPopFirst, &ListPopFirst);
    test(1000000, 5, popFirstLabel, &VectorPopFirst, &ListPopFirst);
    test(10000000, 5, popFirstLabel, &VectorPopFirst, &ListPopFirst);

    test(1000, 1, copyLabel, &VectorCopy, &ListCopy);
    test(10000, 1, copyLabel, &VectorCopy, &ListCopy);
    test(100000, 1, copyLabel, &VectorCopy, &ListCopy);
    test(1000000, 1, copyLabel, &VectorCopy, &ListCopy);
    test(10000000, 1, copyLabel, &VectorCopy, &ListCopy);

    return 0;
}
