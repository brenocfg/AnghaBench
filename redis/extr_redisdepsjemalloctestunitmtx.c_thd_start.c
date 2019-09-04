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
struct TYPE_2__ {int /*<<< orphan*/  mtx; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ thd_start_arg_t ;

/* Variables and functions */
 unsigned int NINCRS ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *
thd_start(void *varg) {
	thd_start_arg_t *arg = (thd_start_arg_t *)varg;
	unsigned i;

	for (i = 0; i < NINCRS; i++) {
		mtx_lock(&arg->mtx);
		arg->x++;
		mtx_unlock(&arg->mtx);
	}
	return NULL;
}