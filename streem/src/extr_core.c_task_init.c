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
struct strm_worker {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  th; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* malloc (int) ; 
 void* prod_queue ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 void* queue ; 
 int /*<<< orphan*/  strm_event_loop_started ; 
 int /*<<< orphan*/  strm_init_io_loop () ; 
 void* strm_queue_new () ; 
 int /*<<< orphan*/  task_loop ; 
 int worker_count () ; 
 int worker_max ; 
 TYPE_1__* workers ; 

__attribute__((used)) static void
task_init()
{
  int i;

  if (workers) return;

  strm_event_loop_started = TRUE;
  strm_init_io_loop();

  queue = strm_queue_new();
  prod_queue = strm_queue_new();
  worker_max = worker_count();
  workers = malloc(sizeof(struct strm_worker)*worker_max);
  for (i=0; i<worker_max; i++) {
    pthread_create(&workers[i].th, NULL, task_loop, &workers[i]);
  }
}