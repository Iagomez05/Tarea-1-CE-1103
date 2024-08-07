#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include "SortingAlgorithm.h"

class BubbleSort : public SortingAlgorithm {
public:
    void sort(PagedArray& arr, int size) override;
};

#endif // BUBBLESORT_H
