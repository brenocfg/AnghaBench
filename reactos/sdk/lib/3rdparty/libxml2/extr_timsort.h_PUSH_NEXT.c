#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * storage; } ;
struct TYPE_7__ {size_t start; size_t length; } ;
typedef  TYPE_1__ TIM_SORT_RUN_T ;
typedef  TYPE_2__ TEMP_STORAGE_T ;
typedef  int /*<<< orphan*/  SORT_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  BINARY_INSERTION_SORT_START (int /*<<< orphan*/ *,size_t,size_t) ; 
 size_t COUNT_RUN (int /*<<< orphan*/ *,size_t,size_t const) ; 
 int /*<<< orphan*/  TIM_SORT_MERGE (int /*<<< orphan*/ *,TYPE_1__*,size_t,TYPE_2__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline int PUSH_NEXT(SORT_TYPE *dst,
                              const size_t size,
                              TEMP_STORAGE_T *store,
                              const size_t minrun,
                              TIM_SORT_RUN_T *run_stack,
                              size_t *stack_curr,
                              size_t *curr) {
  size_t len = COUNT_RUN(dst, *curr, size);
  size_t run = minrun;

  if (run > size - *curr) {
    run = size - *curr;
  }

  if (run > len) {
    BINARY_INSERTION_SORT_START(&dst[*curr], len, run);
    len = run;
  }

  run_stack[*stack_curr].start = *curr;
  run_stack[*stack_curr].length = len;
  (*stack_curr)++;
  *curr += len;

  if (*curr == size) {
    /* finish up */
    while (*stack_curr > 1) {
      TIM_SORT_MERGE(dst, run_stack, *stack_curr, store);
      run_stack[*stack_curr - 2].length += run_stack[*stack_curr - 1].length;
      (*stack_curr)--;
    }

    if (store->storage != NULL) {
      free(store->storage);
      store->storage = NULL;
    }

    return 0;
  }

  return 1;
}