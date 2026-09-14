#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "ISort.h"
#include <stdexcept>
using namespace std;

template<class T>
class QuickSort : public ISort<T> {
private:
    int (*pivotSelection)(T*, int);

public:
    QuickSort(int (*pivotSelection)(T*, int) = 0)
        : pivotSelection(pivotSelection) {}

    void sort(T array[], int size, int (*comparator)(T&, T&) = 0) override {
        // TODO Q4
        (void)array; (void)size; (void)comparator;
        throw logic_error("TODO Q4: QuickSort::sort");
    }

private:
    void quickSort(T array[], int left, int right,
                   int (*comparator)(T&, T&) = 0) {
        // TODO Q4
        (void)array; (void)left; (void)right; (void)comparator;
        throw logic_error("TODO Q4: QuickSort::quickSort");
    }

    int partition(T array[], int left, int right,
                  int (*comparator)(T&, T&) = 0) {
        // TODO Q4
        (void)array; (void)left; (void)right; (void)comparator;
        throw logic_error("TODO Q4: QuickSort::partition");
    }
};

#endif
