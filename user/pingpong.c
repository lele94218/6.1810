#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
  if (argc > 1) {
    const char* message = "Error: command pingpong has no argument.\n";
    write(1, message, strlen(message));
    exit(1);
  }

  int pid;
  int fds[2];
  char buf[1];

  // create a pipe, with two FDs in fds[0], fds[1].
  pipe(fds);

  pid = fork();
  if (pid == 0) {
    read(fds[0], buf, sizeof(buf));
    printf("%d: received ping\n", getpid());
    write(fds[1], "a", 1);
  } else {
    write(fds[1], "a", 1);
    read(fds[0], buf, 1);
    printf("%d: received pong\n", getpid());
  }

  exit(0);
}
