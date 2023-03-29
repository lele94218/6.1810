#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
  if (argc == 1) {
    const char* message = "Error: missing number of ticks.\n";
    write(1, message, strlen(message));
    exit(1);
  }
  const int ticks = atoi(argv[1]);
  sleep(ticks);

  exit(0);
}
