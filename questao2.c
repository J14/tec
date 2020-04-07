#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
  int tid;
  int num;
} thread_data_t;

void *inverse_sequence(void *arg)
{
  thread_data_t *data = (thread_data_t *) arg;
  pthread_t thread;

  if (data->tid <= data->num && data->tid > 0) {
    data->tid++;
    pthread_create(&thread, NULL, inverse_sequence, data);

    pthread_join(thread, NULL);

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

  pthread_t thread;
  int num_threads = atoi(argv[1]);

  thread_data_t *thread_data = (thread_data_t *) malloc(sizeof(thread_data_t));
  thread_data->tid = 1;
  thread_data->num = num_threads;

  pthread_create(&thread, NULL, inverse_sequence, thread_data);

  pthread_join(thread, NULL);

  thread_data->tid--;
  printf("Olá, eu sou a thread %d\n", thread_data->tid);

  free(thread_data);

  return EXIT_SUCCESS;
}
