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
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  callout_cnd ; 
 int /*<<< orphan*/  callout_mtx ; 
 int /*<<< orphan*/ * callout_queue ; 
 int /*<<< orphan*/  callout_thread ; 
 int /*<<< orphan*/  callout_thread_func ; 
 int initialized ; 
 int /*<<< orphan*/  mach_timebase_info (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timebase_info ; 
 int work ; 

void callout_system_init(void) {
  if (initialized) {
    return;
  }

  mach_timebase_info(&timebase_info);
  
  if (pthread_mutex_init(&callout_mtx, NULL)) {
    abort();
  }
  
  if (pthread_cond_init(&callout_cnd, NULL)) {
    abort();
  }
  
  callout_queue = NULL;
  work = false;
  
  if (pthread_create(&callout_thread, /*&attr*/ NULL, &callout_thread_func,
    NULL))
  {
    abort();
  }
  
  initialized = true;
}