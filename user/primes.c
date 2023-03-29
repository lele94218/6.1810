#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
  if (argc > 1) {
    const char* message = "Error: command primes has no argument.\n";
    write(1, message, strlen(message));
    exit(1);
  }

  int fds[100][2];
  int index = 0;
  pipe(fds[index]);
  for (int i = 2; i <= 35; ++i) {
    write(fds[index][1], &i, 4);
  }
  close(fds[index][1]);

  while (fork() == 0) {
    int start;
    if (read(fds[index][0], &start, 4)) {
      printf("prime %d\n", start);
    } else {
      close(fds[index][0]);
      exit(0);
    }

    int num;
    pipe(fds[index + 1]);
    while (read(fds[index][0], &num, 4)) {
      if (num % start) {
        write(fds[index + 1][1], &num, 4);
      }
    }
    close(fds[index][0]);
    close(fds[index + 1][1]);
    index++;
  }
  close(fds[index][0]);
  wait(0);
  exit(0);
}
