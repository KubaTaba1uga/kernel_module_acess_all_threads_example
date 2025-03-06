#include <pthread.h>
#include <stdio.h>

void *thread_function(void *arg) {
  printf("Hello from the spawned thread!\n");
  return NULL;
}

int main(void) {
  pthread_t thread;
  int rc = pthread_create(&thread, NULL, thread_function, NULL);
  if (rc) {
    perror("pthread_create failed");
    return 1;
  }
  printf("Hello from the main thread! Spawned thread ID: %lu\n", thread);
  pthread_join(thread, NULL); // Wait for the spawned thread to finish.
  return 0;
}
