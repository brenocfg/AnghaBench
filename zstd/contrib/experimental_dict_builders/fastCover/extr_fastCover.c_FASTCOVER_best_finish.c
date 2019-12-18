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
typedef  int /*<<< orphan*/  ZDICT_fastCover_params_t ;
struct TYPE_3__ {size_t liveJobs; size_t compressedSize; size_t dictSize; int /*<<< orphan*/  cond; int /*<<< orphan*/  mutex; int /*<<< orphan*/  parameters; scalar_t__ dict; } ;
typedef  TYPE_1__ FASTCOVER_best_t ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GENERIC ; 
 int /*<<< orphan*/  ZSTD_pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void*,size_t) ; 

__attribute__((used)) static void FASTCOVER_best_finish(FASTCOVER_best_t *best, size_t compressedSize,
                              ZDICT_fastCover_params_t parameters, void *dict,
                              size_t dictSize) {
  if (!best) {
    return;
  }
  {
    size_t liveJobs;
    ZSTD_pthread_mutex_lock(&best->mutex);
    --best->liveJobs;
    liveJobs = best->liveJobs;
    /* If the new dictionary is better */
    if (compressedSize < best->compressedSize) {
      /* Allocate space if necessary */
      if (!best->dict || best->dictSize < dictSize) {
        if (best->dict) {
          free(best->dict);
        }
        best->dict = malloc(dictSize);
        if (!best->dict) {
          best->compressedSize = ERROR(GENERIC);
          best->dictSize = 0;
          return;
        }
      }
      /* Save the dictionary, parameters, and size */
      memcpy(best->dict, dict, dictSize);
      best->dictSize = dictSize;
      best->parameters = parameters;
      best->compressedSize = compressedSize;
    }
    ZSTD_pthread_mutex_unlock(&best->mutex);
    if (liveJobs == 0) {
      ZSTD_pthread_cond_broadcast(&best->cond);
    }
  }
}