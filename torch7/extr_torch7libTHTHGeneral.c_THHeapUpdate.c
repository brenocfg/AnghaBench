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
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  applyHeapDelta () ; 
 scalar_t__ heapDelta ; 
 scalar_t__ heapMaxDelta ; 
 scalar_t__ heapMinDelta ; 
 int /*<<< orphan*/  maybeTriggerGC (int /*<<< orphan*/ ) ; 

void THHeapUpdate(ptrdiff_t size) {
#ifdef DEBUG
  if (size > 0 && heapDelta > PTRDIFF_MAX - size)
    THError("THHeapUpdate: heapDelta(%td) + increased(%td) > PTRDIFF_MAX, heapDelta overflow!", heapDelta, size);
  if (size < 0 && heapDelta < PTRDIFF_MIN - size)
    THError("THHeapUpdate: heapDelta(%td) + decreased(%td) < PTRDIFF_MIN, heapDelta underflow!", heapDelta, size);
#endif

  heapDelta += size;

  // batch updates to global heapSize to minimize thread contention
  if (heapDelta < heapMaxDelta && heapDelta > heapMinDelta) {
    return;
  }

  ptrdiff_t newHeapSize = applyHeapDelta();

  if (size > 0) {
    maybeTriggerGC(newHeapSize);
  }
}