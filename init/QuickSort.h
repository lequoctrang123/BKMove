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
        quickSort(array, 0, size-1, comparator);
        //(void)array; (void)size; (void)comparator;
        //throw logic_error("TODO Q4: QuickSort::sort");
    }

private:
    void quickSort(T array[], int left, int right,
                   int (*comparator)(T&, T&) = 0) {
        if(left>=right) return;
        int pivotIdx=partition(array, left, right, comparator);
        quickSort(array, left, pivotIdx-1, comparator);
        quickSort(array, pivotIdx+1, right, comparator);
        //(void)array; (void)left; (void)right; (void)comparator;
        //throw logic_error("TODO Q4: QuickSort::quickSort");
    }

    int partition(T array[], int left, int right,
                  int (*comparator)(T&, T&) = 0) {
        int pivotIdx;
        if(pivotSelection){
            int relativeIdx = pivotSelection(array+left, right-left+1);
            pivotIdx=left+relativeIdx;
        }
        else{
            pivotIdx=right;
        }

        int i=left-1;
        swap(array[right], array[pivotIdx]);
        for(int j=left; j<right; j++){
            if(compareElements(array[j], array[right], comparator)<0){
                i++;
                swap(array[j], array[i]);
            }
        }

        i++;
        swap(array[i], array[right]);
        return i;
        //(void)array; (void)left; (void)right; (void)comparator;
        //throw logic_error("TODO Q4: QuickSort::partition");
    }

    int compareElements(T &a, T &b, int (*comparator)(T&, T&) = 0){
        if(comparator){
            return comparator(a, b);
        }

        if(a<b) return -1;
        if(a>b) return 1;
        return 0;
    }
};

#endif
