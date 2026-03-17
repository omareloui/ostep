#include "common_threads.h"
#include <stdio.h>
#include <stdlib.h>

// volatile tells the compiler: "don't optimize away reads/writes to this
// variable — its value can change at any time outside the current code's
// control."
//
// Without it, the compiler might cache counter in a register and never re-read
// it from memory. With volatile, every access goes to the actual memory
// location.
//
// Common use cases: hardware registers (memory-mapped I/O), variables modified
// by interrupt handlers, and variables shared between threads (though volatile
// alone isn't sufficient for thread safety in C — you'd still need atomics or
// mutexes for that).
volatile int counter = 0;
int loops;

void *worker(void *arg) {
  int i;
  for (i = 0; i < loops; i++)
    counter++;

  return NULL;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "usage: threads <value>\n");
    exit(1);
  }

  loops = atoi(argv[1]);
  pthread_t p1, p2;

  printf("Initial value : %d\n", counter);

  Pthread_create(&p1, NULL, worker, NULL);
  Pthread_create(&p2, NULL, worker, NULL);

  Pthread_join(p1, NULL);
  Pthread_join(p2, NULL);

  printf("Final value   : %d\n", counter);

  return 0;
}
