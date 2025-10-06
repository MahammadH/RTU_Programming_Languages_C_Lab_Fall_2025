#include <stdio.h>
#include <stdlib.h>

int main() {
    int num_elements;
    int *arr;
    int sum = 0;
    float average;

    
    printf("Enter number of elements: ");
    scanf("%d", &num_elements);

   
    arr = (int *)malloc(num_elements * sizeof(int));

    
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1; 
    }

    
    printf("Enter %d integers: ", num_elements);
    for (int i = 0; i < num_elements; i++) {
        scanf("%d", &arr[i]);
        sum += arr[i];
    }

    
    average = (float)sum / num_elements;

    
    printf("Sum = %d\n", sum);
    printf("Average = %.2f\n", average);

   
    free(arr);

    return 0; 
} 
