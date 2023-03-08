#include <iostream>
#include <omp.h>
using namespace std;

int multiply_parlel( int* col,int* row, int n) {
    int result = 0;
    for (int i = 0; i < n; i++) {
        result += row[i] * col[i];
    }
    return result;
}

int main1() {
    int m1, n1, m2, n2;
    cout << "Enter the dimensions of matrix 1 (m x n): " << endl;
    cin >> m1 >> n1;
    cout << "Enter the dimensions of matrix 2 (m x n): " << endl;
    cin >> m2 >> n2;

    if (n1 != m2) {
        cout << "Error: The number of columns in matrix 1 must be equal to the number of rows in matrix 2." << endl;
        return 0;
    }

    int** a = new int*[m1];
    for (int i = 0; i < m1; i++) {
        a[i] = new int[n1];
    }

    int** b = new int*[m2];
    for (int i = 0; i < m2; i++) {
        b[i] = new int[n2];
    }

    int** c = new int*[m1];
    for (int i = 0; i < m1; i++) {
        c[i] = new int[n2];
    }

    for (int i = 0; i < m1; i++) {
        for (int j = 0; j < n1; j++) {
            a[i][j] = rand() % 100;
            cout << a[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < m2; i++) {
        for (int j = 0; j < n2; j++) {
            b[i][j] = rand() % 100;
            cout << b[i][j] << " ";
        }
        cout << endl;
    }

    float total_s = 0;
    for (int run = 0; run < 100; run++)
    {
        float start_time_r = omp_get_wtime();

#pragma omp parallel for static
        for (int i = 0; i < m1; i++) {
            for (int j = 0; j < n2; j++) {
                int* row = a[i];
                int* col = new int[m2];
                for (int k = 0; k < m2; k++) {
                    col[k] = b[k][j];
                }
                c[i][j] = multiply_parlel(col, row, n1);
                delete[] col;
            }
        }
        float end_time_r = omp_get_wtime();
        total_s += end_time_r - start_time_r;
    }
    float total_d=0;
    for (int run = 0; run < 100; run++)
    {
        float start_time_r = omp_get_wtime();

#pragma omp parallel for dynamic
        for (int i = 0; i < m1; i++) {
            for (int j = 0; j < n2; j++) {
                int* row = a[i];
                int* col = new int[m2];
                for (int k = 0; k < m2; k++) {
                    col[k] = b[k][j];
                }
                c[i][j] = multiply_parlel(col, row, n1);
                delete[] col;
            }
        }
        float end_time_r = omp_get_wtime();
        total_d += end_time_r - start_time_r;
    }

    float total_g = 0;
    for (int run = 0; run < 100; run++)
    {
        float start_time_r = omp_get_wtime();

#pragma omp parallel for guided
        for (int i = 0; i < m1; i++) {
            for (int j = 0; j < n2; j++) {
                int* row = a[i];
                int* col = new int[m2];
                for (int k = 0; k < m2; k++) {
                    col[k] = b[k][j];
                }
                c[i][j] = multiply_parlel(col, row, n1);
                delete[] col;
            }
        }
        float end_time_r = omp_get_wtime();
        total_g += end_time_r - start_time_r;
    }

    cout << "Resulting matrix: " << endl;
    for (int i = 0; i < m1; i++) {
          for (int j = 0; j < n2; j++) {
               cout << c[i][j] << " ";
        }
        cout << endl;
    }

  

    float total_s_n = 0;
    for (int run = 0; run < 100; run++)
    {
        float start_time_r = omp_get_wtime();

#pragma omp parallel for static thread_num(n1)
        for (int i = 0; i < m1; i++) {
            for (int j = 0; j < n2; j++) {
                int* row = a[i];
                int* col = new int[m2];
                for (int k = 0; k < m2; k++) {
                    col[k] = b[k][j];
                }
                c[i][j] = multiply_parlel(col, row, n1);
                delete[] col;
            }
        }
        float end_time_r = omp_get_wtime();
        total_s_n += end_time_r - start_time_r;
    }

    float total_d_n = 0;
    for (int run = 0; run < 100; run++)
    {
        float start_time_r = omp_get_wtime();

#pragma omp parallel for dynamic thread_num(n1)
        for (int i = 0; i < m1; i++) {
            for (int j = 0; j < n2; j++) {
                int* row = a[i];
                int* col = new int[m2];
                for (int k = 0; k < m2; k++) {
                    col[k] = b[k][j];
                }
                c[i][j] = multiply_parlel(col, row, n1);
                delete[] col;
            }
        }
        float end_time_r = omp_get_wtime();
        total_d_n += end_time_r - start_time_r;
    }

    float total_g_n = 0;
    for (int run = 0; run < 100; run++)
    {
        float start_time_r = omp_get_wtime();

#pragma omp parallel for guided thread_num(n1)
        for (int i = 0; i < m1; i++) {
            for (int j = 0; j < n2; j++) {
                int* row = a[i];
                int* col = new int[m2];
                for (int k = 0; k < m2; k++) {
                    col[k] = b[k][j];
                }
                c[i][j] = multiply_parlel(col, row, n1);
                delete[] col;
            }
        }
        float end_time_r = omp_get_wtime();
        total_g_n += end_time_r - start_time_r;
    }

    cout << "Resulting matrix: " << endl;
    for (int i = 0; i < m1; i++) {
        for (int j = 0; j < n2; j++) {
            cout << c[i][j] << " ";
        }
        cout << endl;
    }


    float total_s_1 = 0;
    for (int run = 0; run < 100; run++)
    {
        float start_time_r = omp_get_wtime();

#pragma omp parallel for (static,1)
        for (int i = 0; i < m1; i++) {
            for (int j = 0; j < n2; j++) {
                int* row = a[i];
                int* col = new int[m2];
                for (int k = 0; k < m2; k++) {
                    col[k] = b[k][j];
                }
                c[i][j] = multiply_parlel(col, row, n1);
                delete[] col;
            }
        }
        float end_time_r = omp_get_wtime();
        total_s_1 += end_time_r - start_time_r;
    }

    float total_d_1 = 0;
    for (int run = 0; run < 100; run++)
    {
        float start_time_r = omp_get_wtime();

#pragma omp parallel for (dynamic,1)
        for (int i = 0; i < m1; i++) {
            for (int j = 0; j < n2; j++) {
                int* row = a[i];
                int* col = new int[m2];
                for (int k = 0; k < m2; k++) {
                    col[k] = b[k][j];
                }
                c[i][j] = multiply_parlel(col, row, n1);
                delete[] col;
            }
        }
        float end_time_r = omp_get_wtime();
        total_d_1 += end_time_r - start_time_r;
    }

    float total_g_1 = 0;
    for (int run = 0; run < 100; run++)
    {
        float start_time_r = omp_get_wtime();

#pragma omp parallel for (guided,1)
        for (int i = 0; i < m1; i++) {
            for (int j = 0; j < n2; j++) {
                int* row = a[i];
                int* col = new int[m2];
                for (int k = 0; k < m2; k++) {
                    col[k] = b[k][j];
                }
                c[i][j] = multiply_parlel(col, row, n1);
                delete[] col;
            }
        }
        float end_time_r = omp_get_wtime();
        total_g_1 += end_time_r - start_time_r;
    }

    float total_s_r = 0;
    for (int run = 0; run < 100; run++)
    {
        float start_time_r = omp_get_wtime();

#pragma omp parallel for (static,rand()%100)
        for (int i = 0; i < m1; i++) {
            for (int j = 0; j < n2; j++) {
                int* row = a[i];
                int* col = new int[m2];
                for (int k = 0; k < m2; k++) {
                    col[k] = b[k][j];
                }
                c[i][j] = multiply_parlel(col, row, n1);
                delete[] col;
            }
        }
        float end_time_r = omp_get_wtime();
        total_s_r += end_time_r - start_time_r;
    }

    float total_d_r = 0;
    for (int run = 0; run < 100; run++)
    {
        float start_time_r = omp_get_wtime();

#pragma omp parallel for (dynamic,rand()%100)
        for (int i = 0; i < m1; i++) {
            for (int j = 0; j < n2; j++) {
                int* row = a[i];
                int* col = new int[m2];
                for (int k = 0; k < m2; k++) {
                    col[k] = b[k][j];
                }
                c[i][j] = multiply_parlel(col, row, n1);
                delete[] col;
            }
        }
        float end_time_r = omp_get_wtime();
        total_d_r += end_time_r - start_time_r;
    }

    float total_g_r = 0;
    for (int run = 0; run < 100; run++)
    {
        float start_time_r = omp_get_wtime();

#pragma omp parallel for (guided,rand%100)
        for (int i = 0; i < m1; i++) {
            for (int j = 0; j < n2; j++) {
                int* row = a[i];
                int* col = new int[m2];
                for (int k = 0; k < m2; k++) {
                    col[k] = b[k][j];
                }
                c[i][j] = multiply_parlel(col, row, n1);
                delete[] col;
            }
        }
        float end_time_r = omp_get_wtime();
        total_g_r += end_time_r - start_time_r;
    }

    cout << "Time used is for 100 Runs for all" << endl;
    cout << "Execution Time for default with static:" << total_s<< endl;
    cout << "Execution Time for default with dynamic:" << total_d << endl;
    cout << "Execution Time for default with guided:" << total_g << endl;
    cout << "Execution Time for rows with static:" << total_s_n << endl;
    cout << "Execution Time for rows with dynamic:" << total_d_n << endl;
    cout << "Execution Time for rows with guided:" << total_g_n << endl;
    cout << "Execution Time for random thread with static:" << total_s_r << endl;
    cout << "Execution Time for random thread with dynamic:" << total_d_r << endl;
    cout << "Execution Time for random thread with guided:" << total_g_r << endl;
    cout << "Execution Time for 1 thread with static:" << total_s_1 << endl;
    cout << "Execution Time for 1 thread with dynamic:" << total_d_1 << endl;
    cout << "Execution Time for 1 thread with guided:" << total_g_1 << endl;
   

    for (int i = 0; i < m1; i++) {
        delete[] a[i];
    }
     delete[] a;

    for (int i = 0; i < m2; i++) {
        delete[] b[i];
    }
      delete[] b;

    for (int i = 0; i < m1; i++) {
        delete[] c[i];
    }
    delete[] c;

    return 0;
}