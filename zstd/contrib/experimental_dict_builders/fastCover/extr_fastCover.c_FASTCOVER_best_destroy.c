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
struct TYPE_4__ {int /*<<< orphan*/  cond; int /*<<< orphan*/  mutex; scalar_t__ dict; } ;
typedef  TYPE_1__ FASTCOVER_best_t ;

/* Variables and functions */
 int /*<<< orphan*/  FASTCOVER_best_wait (TYPE_1__*) ; 
 int /*<<< orphan*/  ZSTD_pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 

__attribute__((used)) static void FASTCOVER_best_destroy(FASTCOVER_best_t *best) {
  if (!best) {
    return;
  }
  FASTCOVER_best_wait(best);
  if (best->dict) {
    free(best->dict);
  }
  ZSTD_pthread_mutex_destroy(&best->mutex);
  ZSTD_pthread_cond_destroy(&best->cond);
}