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
struct callout {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_mtx ; 
 int /*<<< orphan*/  callout_stop_safe_locked (struct callout*,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int callout_stop_safe(struct callout *c, int drain) {
  pthread_mutex_lock(&callout_mtx);
  callout_stop_safe_locked(c, drain);
  pthread_mutex_unlock(&callout_mtx);
  return 0;
}