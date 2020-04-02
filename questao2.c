#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
  int tid;
  int num;
  pthread_t *threads;
} thread_data_t;

void *inverse_sequence(void *arg)
{
  thread_data_t *data = (thread_data_t *) arg;

  if (data->tid <= data->num && data->tid > 0) {
    data->tid++;
    pthread_create(&data->threads[data->tid - 1], NULL, inverse_sequence, data);

    pthread_join(data->threads[data->tid - 1], NULL);

    data->tid--;
    printf("Olá, eu sou a thread %d\n", data->tid);
  }

  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  if (argc != 2) {
    printf("Usage -> %s <num_threads>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int num_threads = atoi(argv[1]);

  thread_data_t *thread_data = (thread_data_t *) malloc(sizeof(thread_data_t));
  thread_data->threads = (pthread_t *) malloc(sizeof(pthread_t) * num_threads);
  thread_data->tid = 1;
  thread_data->num = num_threads;

  pthread_create(thread_data->threads, NULL, inverse_sequence, thread_data);

  pthread_join(*thread_data->threads, NULL);

  thread_data->tid--;
  printf("Olá, eu sou a thread %d\n", thread_data->tid);

  free(thread_data);

  return EXIT_SUCCESS;
}
