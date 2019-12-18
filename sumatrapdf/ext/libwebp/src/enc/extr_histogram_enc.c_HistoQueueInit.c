#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int max_size; int /*<<< orphan*/ * queue; scalar_t__ size; } ;
typedef  int /*<<< orphan*/  HistogramPair ;
typedef  TYPE_1__ HistoQueue ;

/* Variables and functions */
 scalar_t__ WebPSafeMalloc (int,int) ; 

__attribute__((used)) static int HistoQueueInit(HistoQueue* const histo_queue, const int max_size) {
  histo_queue->size = 0;
  histo_queue->max_size = max_size;
  // We allocate max_size + 1 because the last element at index "size" is
  // used as temporary data (and it could be up to max_size).
  histo_queue->queue = (HistogramPair*)WebPSafeMalloc(
      histo_queue->max_size + 1, sizeof(*histo_queue->queue));
  return histo_queue->queue != NULL;
}