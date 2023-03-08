#include <iostream>
#include <omp.h>
using namespace std;

// Function to partition the array for Quick Sort
int partition(int arr[], int start_index, int end_index) {
    int pivot = arr[end_index];
    int i = start_index - 1;

    for (int j = start_index; j <= end_index - 1; j++) {
        if (arr[j] > pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[end_index]);
    return i + 1;
}


void quicksort(int arr[], int start_index, int end_index) {
    if (start_index < end_index) {
        int partition_index = partition(arr, start_index, end_index);
        #pragma omp parallel sections
        {
            #pragma omp section
            quicksort(arr, start_index, partition_index - 1);


            #pragma omp section
            quicksort(arr, partition_index + 1, end_index);
        }
    }
}

int main() {
    int m, n;
    cout << "Enter the number of rows and columns of the matrix: " << endl;
    cin >> m >> n;

    int** a = new int* [m];
    for (int i = 0; i < m; i++) {
        a[i] = new int[n];
    }
    cout << "Matrix Before Sort" << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = rand() % 100;
            cout << a[i][j] << " ";
        }
        cout << endl;
    }

  
#pragma omp parallel for num_threads(7)
    for (int i = 0; i < m; i++) {
        quicksort(a[i], 0, n - 1);
    }

    cout << "Matrix After Sort" << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < m; i++) {
        delete[] a[i];
    }
    delete[] a;

    return 0;
}
