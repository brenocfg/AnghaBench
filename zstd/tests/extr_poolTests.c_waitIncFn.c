#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  mut; scalar_t__ val; } ;
typedef  TYPE_1__ abruptEndCanary_t ;

/* Variables and functions */
 int /*<<< orphan*/  UTIL_sleepMilli (int) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void waitIncFn(void *opaque) {
  abruptEndCanary_t* test = (abruptEndCanary_t*) opaque;
  UTIL_sleepMilli(10);
  ZSTD_pthread_mutex_lock(&test->mut);
  test->val = test->val + 1;
  ZSTD_pthread_mutex_unlock(&test->mut);
}