/* Giurgiu Razvan - Grupa 2 ( 30422)
 * Am implementat metoda bottom-up build folosind heapify si plecand tot timpul de la
 * heapSize / 2 -1 si urcam spre varful heapului.
 *
 * HeapSort se aseamana cu metoda de bottom-up heap build, incepem de la heapSize / 2 - 1 si stim ca
 * deoarece folosim un MaxHeap tot timpul elementul a[heapSize] este cel mai mare din heap asa ca schimbam valoarea
 * lui a[heapSize] cu valoare lui i si folosim heapify
 *
 * Implementarea metodei top-down adauga la fiecare pas in heap, un nou ulement folosin functia insert.
 *
 * Din grafice se observa ca metoda de construire bottom-up este mai eficienta deoarece are un nr mai mic de comparari si atribuiri
 * */

#include <stdio.h>
#include "Profiler.h"

Profiler p("heap");

#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_TESTS 10

void heapify(int a[], int n, int i) {

    Operation opCompareBottomUp = p.createOperation("CompareBottomUp", n);
    Operation opAttributeBottomUp = p.createOperation("AttributeBottomUp", n);

    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n) {
        opCompareBottomUp.count();
        if (a[left] > a[largest]) {
            largest = left;
            opCompareBottomUp.count();
            opAttributeBottomUp.count();
        }
    }

    if (right < n) {
        opCompareBottomUp.count();
        if (a[right] > a[largest]) {
            largest = right;
            opCompareBottomUp.count();
            opAttributeBottomUp.count();
        }
    }

    if (largest != i) {
        opCompareBottomUp.count();
        opAttributeBottomUp.count(3);
        std::swap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}


void buildMaxHeap(int a[], int heapSize)
{
    for (int i = heapSize / 2 - 1; i >= 0; i--)
        heapify(a, heapSize, i);
}

void demoHeapify()
{
   int a[]={4,10,3,5,1};
   int heapSize = sizeof(a)/sizeof(a[0]);

   buildMaxHeap(a, heapSize);

   for( int i = 0 ; i < heapSize ; i++)
       printf("%d ", a[i]);

}

void heapSort(int a[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    for (int i = n - 1; i > 0; i--) {
        std::swap(a[0], a[i]);

        heapify(a, i, 0);
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

/*void insert( int a[], int *heapSize, int key)
{
    if(*heapSize == 0) {
        a[0] = key;
        *heapSize = *heapSize + 1;
    }else {
        a[*heapSize] = key;
        *heapSize = *heapSize + 1;
        for (int i = *heapSize / 2 - 1; i >= 0; i--)
            heapifyTopDown(a, *heapSize, i);
    }
}*/

int maximum(int a[])
{
    return a[1];
}

int extractMax(int a[], int *heapSize)
{
    if( *heapSize < 1 )
    {
        printf("error");
        return -1;
    }
    int max = a[0];
    a[0]=a[*heapSize-1];
    *heapSize = *heapSize - 1;
    heapify(a,*heapSize,0);
    return max;
}

void heapIncreaseKey(int a[], int i,int len, int key)
{
    Operation opCompareTopDown = p.createOperation("CompareTopDown", len);
    Operation opAttributeTopDown = p.createOperation("AttributeTopDown", len);

    if(key < a[i])
    {
        printf("Key is smaller");
        opCompareTopDown.count();
    }
    else {
        opCompareTopDown.count();
        a[i] = key;
        opAttributeTopDown.count();
        while (i > 1 && a[i/2] < a[i]) {
            opCompareTopDown.count();
            std::swap(a[i/2], a[i]);
            opAttributeTopDown.count(3);
            i = i / 2;
        }
    }
}

void maxHeapInsert(int a[], int *heapSize, int len, int key)
{
    *heapSize = *heapSize + 1;
    a[*heapSize] = -1;
    heapIncreaseKey(a, *heapSize, len, key);
}

void buildMaxHeapTopDown(int a[], int len, int *heapSize)
{
    for (int i = 1 ; i < len ; i++)
        maxHeapInsert(a, heapSize,len, i);
}

void demoHeapTopDown()
{
    int a[]={1,3,7,5,9,2,8};
    int len = sizeof(a)/sizeof(a[0]);
    int heap[MAX_SIZE];
    int  heapSize = 0;


    for( int i = 0 ; i < len  ; i++)
        maxHeapInsert(heap,&heapSize, len,a[i]);

    for( int i = 1 ; i <= heapSize  ; i++)
        printf("%d ", heap[i]);
}

void demoFunction()
{
    int a[]={1,3,7,5,9,2,8};
    int heapSize = sizeof(a)/sizeof(a[0]);
    int  length = heapSize;


    buildMaxHeap(a, heapSize);
    printf("%d \n", extractMax(a,&heapSize));

    for( int i = 0 ; i < length - 1 ; i++)
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
        buildMaxHeap(a,n);
        buildMaxHeapTopDown(a,n,&zero);


    }
    p.divideValues("CompareBottomUp", NR_TESTS);
    p.divideValues("AttributeBottomUp", NR_TESTS);

    p.divideValues("CompareTopDown", NR_TESTS);
    p.divideValues("AttributeTopDown", NR_TESTS);

    p.createGroup("nrOfComparisions","CompareBottomUp","CompareTopDown");
    p.createGroup("nrOfAttr","AttributeBottomUp","AttributeTopDown");

    p.showReport();
}


int main ()
{
    //demoFunction();
    prof(UNSORTED);
    //demoHeapTopDown();

    return 0;
}