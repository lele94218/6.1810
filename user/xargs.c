#include "kernel/types.h"
#include "user/user.h"

#define MAXARGS 10

int main(int argc, char* argv[]) {
  if (argc < 2) {
    const char* message = "Error: command xargs have more than one argument.\n";
    write(1, message, strlen(message));
    exit(1);
  }
  char c;
  char buf[512];
  char* p = buf;
  char* next_argv[MAXARGS];
  for (int i = 1; i < argc; ++i) {
    next_argv[i - 1] = argv[i];
  }
  next_argv[argc - 1] = buf;
  while (read(0, &c, 1) == 1) {
    if (c == '\n') {
      if (fork() == 0) {
        *p++ = '\0';
        exec(argv[1], next_argv);
        exit(0);
      } else {
        p = buf;
        wait(0);
      }
    } else {
      *p++ = c;
    }
  }
  exit(0);
}
