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
struct TYPE_3__ {scalar_t__ liveJobs; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; } ;
typedef  TYPE_1__ COVER_best_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void COVER_best_wait(COVER_best_t *best) {
  if (!best) {
    return;
  }
  ZSTD_pthread_mutex_lock(&best->mutex);
  while (best->liveJobs != 0) {
    ZSTD_pthread_cond_wait(&best->cond, &best->mutex);
  }
  ZSTD_pthread_mutex_unlock(&best->mutex);
}