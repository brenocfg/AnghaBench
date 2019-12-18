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

/* Variables and functions */
 int STRM_OK ; 
 int /*<<< orphan*/  sched_yield () ; 
 scalar_t__ stream_count ; 
 int /*<<< orphan*/  task_init () ; 

int
strm_loop()
{
  if (stream_count == 0) return STRM_OK;
  task_init();
  for (;;) {
    sched_yield();
    if (stream_count == 0) {
      break;
    }
  }
  return STRM_OK;
}