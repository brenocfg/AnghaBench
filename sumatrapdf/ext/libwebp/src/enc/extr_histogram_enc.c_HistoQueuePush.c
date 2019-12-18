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
typedef  int /*<<< orphan*/  VP8LHistogram ;
struct TYPE_8__ {scalar_t__ size; scalar_t__ max_size; TYPE_1__* queue; } ;
struct TYPE_7__ {int idx1; int idx2; double cost_diff; } ;
typedef  TYPE_1__ HistogramPair ;
typedef  TYPE_2__ HistoQueue ;

/* Variables and functions */
 int /*<<< orphan*/  HistoQueueUpdateHead (TYPE_2__* const,TYPE_1__*) ; 
 int /*<<< orphan*/  HistoQueueUpdatePair (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,double,TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static double HistoQueuePush(HistoQueue* const histo_queue,
                             VP8LHistogram** const histograms, int idx1,
                             int idx2, double threshold) {
  const VP8LHistogram* h1;
  const VP8LHistogram* h2;
  HistogramPair pair;

  // Stop here if the queue is full.
  if (histo_queue->size == histo_queue->max_size) return 0.;
  assert(threshold <= 0.);
  if (idx1 > idx2) {
    const int tmp = idx2;
    idx2 = idx1;
    idx1 = tmp;
  }
  pair.idx1 = idx1;
  pair.idx2 = idx2;
  h1 = histograms[idx1];
  h2 = histograms[idx2];

  HistoQueueUpdatePair(h1, h2, threshold, &pair);

  // Do not even consider the pair if it does not improve the entropy.
  if (pair.cost_diff >= threshold) return 0.;

  histo_queue->queue[histo_queue->size++] = pair;
  HistoQueueUpdateHead(histo_queue, &histo_queue->queue[histo_queue->size - 1]);

  return pair.cost_diff;
}