#include <stdio.h>
#include <stdbool.h>
void buildMaxHeap(int arr[100],int n){//whole logic was wrong
    bool isheap = false;
    int k=n,j,left,right,value;
    for(int i=n/2;i>=1;i--){
        k=i;
        value = arr[k];
        isheap=false;
        while(!isheap && 2*k<=n){
            left = 2*k;
            right = 2*k+1;
            if(right<=n && arr[left]<arr[right]){
                left=right;
            }
            if(arr[left]<=value){
                isheap=1;
            }else{
                arr[k]=arr[left];
                k=left;
            }
        }
        arr[k]=value;
    }
}

void heapSort(int array[], int size)
{
    int i, temp;
    buildMaxHeap(array, size);
    for (i = size; i >= 2; i--)
    {
        temp = array[1];
        array[1] = array[i];
        array[i] = temp;
        buildMaxHeap(array, i - 1);
    }
}

int main()
{
    int array[100], size, i;
    printf("Enter the number of elements: ");
    scanf("%d", &size);
    printf("Enter the elements: ");
    for (i = 1; i <= size; i++)
        scanf("%d", &array[i]);
    heapSort(array, size);
    printf("The sorted array is: ");
    for (i = 1; i <= size; i++)
        printf("%d ", array[i]);
    printf("\n");
    return 0;
}