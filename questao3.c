#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int count;

pthread_mutex_t lock;

void *counter(void *arg);

int main(int argc, char *argv[])
{
  pthread_t *threads;
  int n;
  char f;

  if (argc != 3) {
    fprintf(stderr, "Error: Usage => %s <tipo> <num_threads>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  f = argv[1][0];
  n = atoi(argv[2]);

  pthread_mutex_init(&lock, NULL);
  threads = (pthread_t *) malloc(sizeof(pthread_t) * n);

  for (int i = 0; i < n; i++) {
    pthread_create(&threads[i], NULL, counter, NULL);
  }

  if (f == 'E') {
    for (int i = 0; i < n; i++) {
      pthread_join(threads[i], NULL);
    }
  }

  printf("Count: %d\n", count);

  free(threads);

  return EXIT_SUCCESS;
}


void *counter(void *arg)
{
  pthread_mutex_lock(&lock);
  count++;
  pthread_mutex_unlock(&lock);

  pthread_exit(NULL);
}
