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
struct TYPE_3__ {scalar_t__ max_size; scalar_t__ size; int /*<<< orphan*/  queue; } ;
typedef  TYPE_1__ HistoQueue ;

/* Variables and functions */
 int /*<<< orphan*/  WebPSafeFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void HistoQueueClear(HistoQueue* const histo_queue) {
  assert(histo_queue != NULL);
  WebPSafeFree(histo_queue->queue);
  histo_queue->size = 0;
  histo_queue->max_size = 0;
}