#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

typedef struct {
  int tid;
  int tam;
  int *vector;
} thread_data_t;

pthread_mutex_t lock;
int maior;

void *menor(void *arg);

void init_vector(int *vector, int tam);

int main(int argc, char *argv[])
{
  srand((unsigned) time(NULL));
  
  int t, n, tam;
  int *vector;
  pthread_t *threads;
  thread_data_t *data;

  if (argc != 3) {
    printf("Usage: %s <int> <num_threads>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  n = atoi(argv[1]);
  t = atoi(argv[2]);
  tam = n / t;

  threads = (pthread_t *) malloc(sizeof(pthread_t) * t);
  data = (thread_data_t *) malloc(sizeof(thread_data_t) * t);
  vector = (int *) malloc(sizeof(int) * n);
  init_vector(vector, n);

  maior = -1;
  for (int i = 0; i < t; i++) {
    data[i].tid = i;
    data[i].vector = vector + (i * tam);
    if (i == t - 1) {
      tam = n - (tam * i);
    }
    data[i].tam = tam;
    pthread_create(&threads[i], NULL, menor, &data[i]);
  }

  for (int i = 0; i < t; i++) {
    pthread_join(threads[i], NULL);
  }

  printf("Maior: %d\n", maior);

  free(threads);
  free(data);
  free(vector);

  return EXIT_SUCCESS;
}

void *menor(void *arg)
{
  thread_data_t *data = (thread_data_t *) arg;

  for (int i = 0; i < data->tam; i++) {
    pthread_mutex_lock(&lock);
    if (data->vector[i] > maior) {
      maior = data->vector[i];
    }
    pthread_mutex_unlock(&lock);
  }

  pthread_exit(NULL);
}

void init_vector(int *vector, int tam)
{
  for (int i = 0; i < tam; i++) {
    vector[i] = rand() % 100;
  }
}
