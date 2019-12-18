#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * storage; scalar_t__ alloc; } ;
typedef  int /*<<< orphan*/  TIM_SORT_RUN_T ;
typedef  TYPE_1__ TEMP_STORAGE_T ;
typedef  int /*<<< orphan*/  SORT_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  BINARY_INSERTION_SORT (int /*<<< orphan*/ *,size_t const) ; 
 int /*<<< orphan*/  CHECK_INVARIANT (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  PUSH_NEXT (int /*<<< orphan*/ *,size_t const,TYPE_1__*,size_t,int /*<<< orphan*/ *,size_t*,size_t*) ; 
 size_t TIM_SORT_COLLAPSE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,TYPE_1__*,size_t const) ; 
 int TIM_SORT_STACK_SIZE ; 
 size_t compute_minrun (size_t const) ; 

void TIM_SORT(SORT_TYPE *dst, const size_t size) {
  size_t minrun;
  TEMP_STORAGE_T _store, *store;
  TIM_SORT_RUN_T run_stack[TIM_SORT_STACK_SIZE];
  size_t stack_curr = 0;
  size_t curr = 0;

  /* don't bother sorting an array of size 1 */
  if (size <= 1) {
    return;
  }

  if (size < 64) {
    BINARY_INSERTION_SORT(dst, size);
    return;
  }

  /* compute the minimum run length */
  minrun = compute_minrun(size);
  /* temporary storage for merges */
  store = &_store;
  store->alloc = 0;
  store->storage = NULL;

  if (!PUSH_NEXT(dst, size, store, minrun, run_stack, &stack_curr, &curr)) {
    return;
  }

  if (!PUSH_NEXT(dst, size, store, minrun, run_stack, &stack_curr, &curr)) {
    return;
  }

  if (!PUSH_NEXT(dst, size, store, minrun, run_stack, &stack_curr, &curr)) {
    return;
  }

  while (1) {
    if (!CHECK_INVARIANT(run_stack, stack_curr)) {
      stack_curr = TIM_SORT_COLLAPSE(dst, run_stack, stack_curr, store, size);
      continue;
    }

    if (!PUSH_NEXT(dst, size, store, minrun, run_stack, &stack_curr, &curr)) {
      return;
    }
  }
}