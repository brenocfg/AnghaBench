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
struct strm_task {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  excl; int /*<<< orphan*/  queue; } ;
typedef  TYPE_1__ strm_stream ;

/* Variables and functions */
 int /*<<< orphan*/  prod_queue ; 
 int /*<<< orphan*/  queue ; 
 scalar_t__ stream_count ; 
 scalar_t__ strm_atomic_cas (int /*<<< orphan*/ ,int,int) ; 
 void* strm_queue_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_exec (TYPE_1__*,struct strm_task*) ; 

__attribute__((used)) static void*
task_loop(void *data)
{
  strm_stream* strm;

  for (;;) {
    strm = strm_queue_get(queue);
    if (!strm) {
      strm = strm_queue_get(prod_queue);
    }
    if (strm) {
      if (strm_atomic_cas(strm->excl, 0, 1)) {
        struct strm_task* t;

        while ((t = strm_queue_get(strm->queue)) != NULL) {
          task_exec(strm, t);
        }
        strm_atomic_cas(strm->excl, 1, 0);
      }
    }
    if (stream_count == 0) {
      break;
    }
  }
  return NULL;
}