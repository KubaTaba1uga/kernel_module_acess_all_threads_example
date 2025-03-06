#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  pid_t pid = fork();

  if (pid < 0) {
    perror("fork failed");
    return 1;
  }
  if (pid == 0) {
    // Child process
    printf("Hello from the child process!\n");
  } else {
    // Parent process
    printf("Hello from the parent process! Child PID: %d\n", pid);
    wait(NULL); // Wait for the child process to finish.
  }
  return 0;
}
