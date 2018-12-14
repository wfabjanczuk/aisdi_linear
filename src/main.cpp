#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>
#include <chrono>

#include "Vector.h"
#include "LinkedList.h"

using namespace std;

#define prependLabel "PREPEND PERFORMANCE TEST"
#define popLastLabel "POP LAST PERFORMANCE TEST"
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

void VectorPopLast(Vector<int>& vector) {
    vector.popLast();
}

void ListPopLast(LinkedList<int>& list) {
    list.popLast();
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
    cout << "> Vector elapsed time: " << elapsed.count() << " s\n";

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < repeat_count; i++) {
        listTest(list);
    }
    finish = chrono::high_resolution_clock::now();
    elapsed = finish - start;
    cout << ">   List elapsed time: " << elapsed.count() << " s\n\n";
}

int main() {

    test(1000, 5, prependLabel, &VectorPrepend, &ListPrepend);
    test(10000, 5, prependLabel, &VectorPrepend, &ListPrepend);
    test(100000, 5, prependLabel, &VectorPrepend, &ListPrepend);
    test(1000000, 5, prependLabel, &VectorPrepend, &ListPrepend);
    test(10000000, 5, prependLabel, &VectorPrepend, &ListPrepend);

    test(1000, 5, popLastLabel, &VectorPopLast, &ListPopLast);
    test(10000, 5, popLastLabel, &VectorPopLast, &ListPopLast);
    test(100000, 5, popLastLabel, &VectorPopLast, &ListPopLast);
    test(1000000, 5, popLastLabel, &VectorPopLast, &ListPopLast);
    test(10000000, 5, popLastLabel, &VectorPopLast, &ListPopLast);

    test(1000, 1, copyLabel, &VectorCopy, &ListCopy);
    test(10000, 1, copyLabel, &VectorCopy, &ListCopy);
    test(100000, 1, copyLabel, &VectorCopy, &ListCopy);
    test(1000000, 1, copyLabel, &VectorCopy, &ListCopy);
    test(10000000, 1, copyLabel, &VectorCopy, &ListCopy);

    return 0;
}
