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
typedef  int ptrdiff_t ;

/* Variables and functions */
 int applyHeapDelta () ; 
 int heapSoftmax ; 
 int heapSoftmaxGrowthFactor ; 
 int heapSoftmaxGrowthThresh ; 
 int /*<<< orphan*/  torchGCData ; 
 int /*<<< orphan*/  torchGCFunction (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void maybeTriggerGC(ptrdiff_t curHeapSize) {
  if (torchGCFunction && curHeapSize > heapSoftmax) {
    torchGCFunction(torchGCData);

    // ensure heapSize is accurate before updating heapSoftmax
    ptrdiff_t newHeapSize = applyHeapDelta();

    if (newHeapSize > heapSoftmax * heapSoftmaxGrowthThresh) {
      heapSoftmax = (ptrdiff_t)(heapSoftmax * heapSoftmaxGrowthFactor);
    }
  }
}