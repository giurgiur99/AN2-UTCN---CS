
/* I have implemented heapSort and which always takes the smallest element
 * from the max-heap ( which is a[heapSize] ) and print it
 *
 * I made the implementation for QuickSort. The algorithm is a divide-et-impera
 * algorithm so it splits the array in smaller arrays and sort them. When the
 * recursivity ends, the array is sorted;
 *
 * I have also implemented QuickSelect ( Rndomized - slect ) which acts almost the same
 * as QuickSort but the pivot is chosen randomly
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Profiler.h"

Profiler p("sort");

#define MAX_SIZE 5000
#define STEP_SIZE 100
#define NR_TESTS 50

int partition( int a[], int l, int r, Operation opCompareQuickSort, Operation opAttributeQuickSort)
{

    int c=0;
    int attr=0;
    int x = a[r]; opAttributeQuickSort.count();
    int i = l - 1; opAttributeQuickSort.count();
    for(int j = l ; j < r ; j++) {
        if (a[j] <= x) {
            //opCompareQuickSort.count();
            c++;
            i++;
            std::swap(a[i], a[j]);
            attr+=3;
            //opAttributeQuickSort.count(3);
        }
    }
         std::swap(a[i+1], a[r]);
        opAttributeQuickSort.count(3);
        opAttributeQuickSort.count(attr);
        opCompareQuickSort.count(c);
        return (i + 1);
}

void quickSort(int a[], int l, int r, int n)
{
    Operation opCompareQuickSort = p.createOperation("CompareQuickSort", n);
    Operation opAttributeQuickSort = p.createOperation("AttributeQuickSort", n);

    if(l < r)
    {
        //opCompareQuickSort.count();
        int q=partition(a,l,r,opCompareQuickSort,opAttributeQuickSort); opAttributeQuickSort.count();
        quickSort(a,l,q-1,n);
        quickSort(a,q+1,r,n);
    }
}

void demoQuickSort()
{
    int a[]={1,5,4,3,82,81,24};
    int length = sizeof(a)/sizeof(a[0]);

    quickSort(a,0,length-1,length);

    for( int i = 0 ; i < length ; i++)
        printf("%d ", a[i]);
}

int randomizedPartition( int a[], int l, int r)
{
    Operation opCompareQuickSort = p.createOperation("CompareQuickSort1", l+r);
    Operation opAttributeQuickSort = p.createOperation("AttributeQuickSort1", l+r);

    srand(time(NULL));
    int i = rand()%r + l;
    int c=0, attr=0;
    std::swap(a[r],a[i]);
    return partition(a,l,r,opCompareQuickSort, opAttributeQuickSort);
}

void randomizedQuicksort(int a[], int l, int r)
{
    if( l < r )
    {
        int q=randomizedPartition(a,l,r);
        randomizedQuicksort(a,l,q-1);
        randomizedPartition(a,q+1,r);

    }
}

void demoRandomizedQuickSort()
{
    int a[]={1,5,4,3,82,81,24};
    int length = sizeof(a)/sizeof(a[0]);

    randomizedQuicksort(a,0,length-1);

    for( int i = 0 ; i < length ; i++)
        printf("%d ", a[i]);
}


void heapify(int a[], int n, int i,  Operation opCompareHeap,  Operation opAttributeHeap)
{
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if(left < n) {
        opCompareHeap.count();
        if (a[left] > a[largest]) {
            opCompareHeap.count();
            opAttributeHeap.count();
            largest = left;
        }
    }

    if(right < n)
    {
        opCompareHeap.count();
        if(a[right] > a[largest])
        {
            opCompareHeap.count();
            opAttributeHeap.count();
            largest = right;
        }
    }

    if(largest != i )
    {
        opCompareHeap.count();
        opAttributeHeap.count(3);
        std::swap(a[i], a[largest]);
        heapify(a,n,largest,opCompareHeap ,opAttributeHeap);
    }
}

void heapSort(int a[], int n) {

    Operation opCompareHeap = p.createOperation("CompareHeapSort",n);
    Operation opAttributeHeap = p.createOperation("AttributeHeapSort", n);

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i, opCompareHeap, opAttributeHeap);

    for (int i = n - 1; i > 0; i--) {
        std::swap(a[0], a[i]);
        opAttributeHeap.count(3);
        heapify(a, i, 0, opCompareHeap, opAttributeHeap);
    }
}

void demoHeapSort ()
{
    int a[]={1,3,7,5,9,2,8};
    int heapSize = sizeof(a)/sizeof(a[0]);
    int  length = heapSize;

    //buildMaxHeap(a, heapSize);
    heapSort(a,heapSize);

    for( int i = 0 ; i < length ; i++)
        printf("%d ", a[i]);
}

void prof(int order)
{
    int a[MAX_SIZE],b[MAX_SIZE];
    int n;


    for( n = STEP_SIZE ; n<=MAX_SIZE ; n+=STEP_SIZE)
    {
        FillRandomArray(a,n);
        int *v = a;
        int zero = 0;
        heapSort(a,n);
        quickSort(v,0,n-1,n);


    }
    p.divideValues("CompareQuickSort", NR_TESTS);
    p.divideValues("AttributeQuickSort", NR_TESTS);

    p.divideValues("CompareTopDown", NR_TESTS);
    p.divideValues("AttributeTopDown", NR_TESTS);

    p.createGroup("nrOfComparisions","CompareQuickSort","CompareHeapSort");
    p.createGroup("nrOfAttr","AttributeQuickSort","AttributeHeapSort");

    p.showReport();
}

int main() {

  // demoHeapSort();
   //demoRandomizedQuickSort();
    prof(UNSORTED);



    return 0;
}
