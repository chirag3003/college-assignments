#include <stdio.h>


void acceptSparseMatrix(int *rows, int *cols, int *numNonZero, int rowArray[], int colArray[], int valueArray[])
{
    printf("Enter the number of rows: ");
    scanf("%d", rows);
    printf("Enter the number of columns: ");
    scanf("%d", cols);

    printf("Enter the number of non-zero elements: ");
    scanf("%d", numNonZero);

    printf("Enter the triplet form (row, column, value) of each non-zero element:\n");
    for (int i = 0; i < *numNonZero; i++)
    {
        printf("Element %d: ", i + 1);
        scanf("%d %d %d", &rowArray[i], &colArray[i], &valueArray[i]);
    }
}

void displayTripletForm(int rows, int cols, int numNonZero, int rowArray[], int colArray[], int valueArray[])
{
    printf("Triplet form of the sparse matrix:\n");
    printf("Row Column Value\n");
    for (int i = 0; i < numNonZero; i++)
    {
        printf("%d    %d    %d\n", rowArray[i], colArray[i], valueArray[i]);
    }
}

int main()
{
    int rows, cols, numNonZero;
    int rowArray[100], colArray[100], valueArray[100];

    acceptSparseMatrix(&rows, &cols, &numNonZero, rowArray, colArray, valueArray);
    displayTripletForm(rows, cols, numNonZero, rowArray, colArray, valueArray);

    return 0;
}