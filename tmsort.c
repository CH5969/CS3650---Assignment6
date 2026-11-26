/** 
 * Threaded Merge Sort
 *
 * Modify this file to implement your multi-threaded version of merge sort. 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>

#include <assert.h>
#include <pthread.h>

#include "timing.h"

#define tty_printf(...) (isatty(1) && isatty(0) ? printf(__VA_ARGS__) : 0)

#ifndef SHUSH
#define log(...) (fprintf(stderr, __VA_ARGS__))
#else 
#define log(...)
#endif

/** The number of threads to be used for sorting. Default: 1 */
int thread_count = 1;

/**
 * Data passed to a worker thread for parallel merge sort.
 *
 * Assumes:
 * - nums and target are separate arrays of the same size.
 * - Both hold the same values in [from, to) at the start.
 * - threads >= 1 is the total threads allowed for this slice.
 */
typedef struct {
  long *nums;
  long *target;
  int from;
  int to;
  int threads;
} sort_args_t;

/* Forward declaration so sort_worker can call merge_sort_parallel. */
static void merge_sort_parallel(long nums[], int from, int to, long target[],
                                int threads);

/**
 * Print the given array of longs, an element per line.
 */
void print_long_array(const long *array, int count) {
  for (int i = 0; i < count; ++i) {
    printf("%ld\n", array[i]);
  }
}

/**
 * Merge two slices of nums into the corresponding portion of target.
 */
void merge(long nums[], int from, int mid, int to, long target[]) {
  int left = from;
  int right = mid;

  int i = from;
  for (; i < to && left < mid && right < to; i++) {
    if (nums[left] <= nums[right]) {
      target[i] = nums[left];
      left++;
    }
    else {
      target[i] = nums[right];
      right++;
    }
  }
  if (left < mid) {
    memmove(&target[i], &nums[left], (mid - left) * sizeof(long));
  }
  else if (right < to) {
    memmove(&target[i], &nums[right], (to - right) * sizeof(long));
  }

}


/**
 * Sort the given slice of nums into target.
 *
 * Warning: nums gets overwritten.
 */
void merge_sort_aux(long nums[], int from, int to, long target[]) {
  if (to - from <= 1) {
    return;
  }

  int mid = (from + to) / 2;
  merge_sort_aux(target, from, mid, nums);
  merge_sort_aux(target, mid, to, nums);
  merge(nums, from, mid, to, target);
}

/**
 * Pick a split index mid in (from, to) based on the thread ratio.
 *
 * Args:
 * - from: start index (included)
 * - to: end index (not included)
 * - left_threads: threads given to the left side (>= 1)
 * - threads: total threads for both sides (>= 2)
 *
 * Returns:
 * - Split index mid strictly between from and to.
 *
 * Assumes:
 * - to - from >= threads and left_threads < threads.
 */
static int get_split_index(int from, int to, int left_threads, int threads) {
  assert(from < to);
  assert(threads >= 2);
  assert(left_threads >= 1 && left_threads < threads);

  /* Use long math so large array sizes do not overflow int. */
  long left_size = ((long)(to - from) * left_threads) / threads;
  return from + (int)left_size;
}

/**
 * Entry point for pthread_create. Sorts one slice in a worker thread.
 *
 * Args:
 * - arg: pointer to a sort_args_t struct owned by the parent thread
 *
 * Returns:
 * - Always returns NULL.
 *
 * Assumes:
 * - arg is not NULL and stays valid until this thread is joined.
 */
static void *sort_worker(void *arg) {
  assert(arg != NULL);
  sort_args_t *args = (sort_args_t *)arg;
  merge_sort_parallel(args->nums, args->from, args->to,
                      args->target, args->threads);
  return NULL;
}

/**
 * Sort nums[from..to) into target[from..to) using `threads` threads.
 *
 * Thread plan:
 * - Creates (threads - 1) worker threads when count >= threads, so total
 *   threads including main equals `threads`.
 * - A new thread sorts [from, mid) while the current thread sorts [mid, to).
 * - Joins the worker before merge() and before return, so left_args on the
 *   stack stays safe.
 * - No locks needed because the two halves never touch the same indexes.
 *
 * Args:
 * - nums: working array (gets overwritten)
 * - from: start index (included)
 * - to: end index (not included)
 * - target: output array that holds the sorted slice when done
 * - threads: total threads allowed for this slice (>= 1)
 *
 * Assumes:
 * - nums and target are not NULL and start with the same values in [from, to).
 */
static void merge_sort_parallel(long nums[], int from, int to, long target[],
                                int threads) {
  assert(nums != NULL && target != NULL);
  assert(from <= to && threads >= 1);

  int count = to - from;
  if (count <= 1) {
    return;
  }
  if (threads == 1) {
    merge_sort_aux(nums, from, to, target);
    return;
  }

  /* Cap threads at item count so every branch has at least one item. */
  if (threads > count) {
    threads = count;
  }

  int left_threads = threads / 2;
  int right_threads = threads - left_threads;
  int mid = get_split_index(from, to, left_threads, threads);

  sort_args_t left_args = {target, nums, from, mid, left_threads};
  pthread_t worker;
  int err = pthread_create(&worker, NULL, sort_worker, &left_args);

  if (err != 0) {
    /* Fall back to single-threaded sort if a thread cannot be made. */
    log("pthread_create failed (%s); running sequentially.\n", strerror(err));
    merge_sort_aux(target, from, mid, nums);
    merge_sort_aux(target, mid, to, nums);
  } else {
    merge_sort_parallel(target, mid, to, nums, right_threads);
    if ((err = pthread_join(worker, NULL)) != 0) {
      fprintf(stderr, "pthread_join failed: %s\n", strerror(err));
      exit(1);
    }
  }

  merge(nums, from, mid, to, target);
}


/**
 * Sort the given array and return the sorted version.
 *
 * The result is malloc'd so it is the caller's responsibility to free it.
 *
 * Warning: The source array gets overwritten.
 */
long *merge_sort(long nums[], int count) {
  long *result = calloc(count, sizeof(long));
  assert(result != NULL);

  memmove(result, nums, count * sizeof(long));

  int threads = thread_count > 0 ? thread_count : 1;
  merge_sort_parallel(nums, 0, count, result, threads);

  return result;
}

/**
 * Based on command line arguments, allocate and populate an input and a 
 * helper array.
 *
 * Returns the number of elements in the array.
 */
int allocate_load_array(int argc, char **argv, long **array) {
  const char *path = argc > 1 ? argv[1] : "-";

  FILE *input = NULL;
  if (strcmp(path, "-") == 0) 
    input = stdin;
  else
    input = fopen(path, "r");

  if (input == NULL) {
    fprintf(stdin, "Error opening file %s: %s", path, strerror(errno));
    exit(1);
  }

  size_t count;
  assert(1 == fscanf(input, "%zu", &count));

  *array = calloc(count, sizeof(long));
  assert(*array != NULL);

  long element;
  size_t i = 0;
  while (i < count && fscanf(input, "%ld", &element) != EOF)  {
    (*array)[i++] = element;
  }

  if (input != stdin) {
    fclose(input);
  }

  log("Read %zu items\n", i);

  return count;
}

int main(int argc, char **argv) {
  stopwatch_t timer;

  if (argc > 1 && strcmp(argv[1], "--help") == 0) {
    fprintf(
        stderr, 
        "Usage: %s <filename>\n\n"
        "The first line of the file should be a count followed by that many lines containing\n"
        "a single decimal integer.\n",
        argv[0]);
    return 1;
  }


  // get the number of threads from the environment variable SORT_THREADS
  if (getenv("MSORT_THREADS") != NULL)
    thread_count = atoi(getenv("MSORT_THREADS"));

  log("Running with %d thread(s). Reading input.\n", thread_count);

  // Read the input
  start_timer(&timer);
  long *array = NULL;
  int count = allocate_load_array(argc, argv, &array);
  stop_timer(&timer);

  log("Array read in %f seconds, beginning sort.\n", 
      time_in_secs(&timer));
 
  // Sort the array
  start_timer(&timer);
  long *result = merge_sort(array, count);
  stop_timer(&timer);
  
  log("Sorting completed in %f seconds.\n", time_in_secs(&timer));

  // Print the result
  start_timer(&timer);
  print_long_array(result, count);
  stop_timer(&timer);
  
  log("Array printed in %f seconds.\n", time_in_secs(&timer));

  free(array);
  free(result);

  return 0;
}