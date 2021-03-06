#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

/*******************************************************************/

float* random_arr(float* arr, int n) {
  const float a = 5.0;
  for(int i = 0; i < n; i++)
    arr[i] = (float)rand() /(float)(RAND_MAX/a);
  return arr;
}

void saxpy_par(int n, float a, float* restrict x, float* restrict y) {
  #pragma omp parallel for default(none) shared(a, n, x, y)
  for (int i = 0; i < n; i++) {
    y[i] = a*x[i] + y[i];
    //printf("Datos modificados de y: %f\n", y[i]);
  }
}

void saxpy(int n, float a, float* restrict x, float* restrict y) {
  for (int i = 0; i < n; i++) {
    y[i] = a*x[i] + y[i];
  //  printf("Datos modificados de y: %f\n", y[i]);
  }
}
/*******************************************************************/
int main(int argc, char* argv[] ) {

  srand(time(NULL));
  double start_time1, run_time1;
  double start_time2, run_time2;
  int n = atoi(argv[1]);
  int a = atoi(argv[2]);
  float* x = (float*) malloc(sizeof(float) * n);
  float* y = (float*) malloc(sizeof(float) * n);

  x = random_arr(x, n);
  y = random_arr(y, n);

  start_time1 = omp_get_wtime();
  saxpy(n, a, x, y);
  run_time1 = omp_get_wtime() - start_time1;
  printf("Tiempo serial: %f segundos\n",run_time1);

  start_time2 = omp_get_wtime();
  saxpy_par(n, a, x, y);
  run_time2 = omp_get_wtime() - start_time2;
  printf("Tiempo paralelo: %f segundos\n",run_time2);

  free(x);
  free(y);
  return 0;
}
