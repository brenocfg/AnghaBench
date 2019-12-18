#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ ptrdiff_t ;

/* Variables and functions */
 scalar_t__ PTRDIFF_MAX ; 
 scalar_t__ PTRDIFF_MIN ; 
 scalar_t__ THAtomicAddPtrdiff (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  THError (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ heapDelta ; 
 int /*<<< orphan*/  heapSize ; 

__attribute__((used)) static ptrdiff_t applyHeapDelta() {
  ptrdiff_t oldHeapSize = THAtomicAddPtrdiff(&heapSize, heapDelta);
#ifdef DEBUG
  if (heapDelta > 0 && oldHeapSize > PTRDIFF_MAX - heapDelta)
    THError("applyHeapDelta: heapSize(%td) + increased(%td) > PTRDIFF_MAX, heapSize overflow!", oldHeapSize, heapDelta);
  if (heapDelta < 0 && oldHeapSize < PTRDIFF_MIN - heapDelta)
    THError("applyHeapDelta: heapSize(%td) + decreased(%td) < PTRDIFF_MIN, heapSize underflow!", oldHeapSize, heapDelta);
#endif
  ptrdiff_t newHeapSize = oldHeapSize + heapDelta;
  heapDelta = 0;
  return newHeapSize;
}