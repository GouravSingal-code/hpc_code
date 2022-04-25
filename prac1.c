#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
int thread_count; // this global variable is shared by all threads
// compiling information -
// gcc name_of_file.c -o name_of_exe -lpthread (link p thread)
// this function is what we want to parallelize
void *Hello(void *rank);
// main driver function of the program
int main(int argc, char *argv[])
{
  long thread;
// /∗ Use long in case of a 64−bit system ∗/
  pthread_t *thread_handles;
// /∗ Get number of threads from command line ∗/
// since the command line arg would be string,
// we convert to the long value
  thread_count = strtol(argv[1], NULL, 10);
// get the thread handles equal to total num
// of threads
  thread_handles = malloc(thread_count * sizeof(pthread_t));
// note : we need to manually startup our threads
// for a particular function which we want to execute in
// the thread
// void* is a pretty nice concept,
// it is essentially a pointer to
// ANY type of memory,

// you just dereference it with the type you expect
// it to be
  for (thread = 0; thread < thread_count; thread++)
    pthread_create(&thread_handles[thread], NULL, Hello, (void *)thread);
// Thread placement on cores is done by OS
  printf("Hello from the main thread\n");
  for (thread = 0; thread < thread_count; thread++)
    pthread_join(thread_handles[thread], NULL);
  free(thread_handles);
  return 0;
}
// /∗ main ∗/
void *Hello(void *rank) // void * means a pointer, can be of any type
{
// Each thread has its own stack
// note : local variables of a thread are
// private to the thread and each thread
// will have its own local copy
  long my_rank = (long)rank;
// /∗ Use long in case of 64−bit system ∗/
  printf("Hello from thread %ld of %d\n", my_rank, thread_count);
  return NULL;
}