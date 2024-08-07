#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include "SortingAlgorithm.h"

class InsertionSort : public SortingAlgorithm {
public:
    void sort(PagedArray& arr, int size) override;
};

#endif // INSERTIONSORT_H
