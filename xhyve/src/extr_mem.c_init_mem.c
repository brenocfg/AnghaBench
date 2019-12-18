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
 int /*<<< orphan*/  RB_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmio_rb_fallback ; 
 int /*<<< orphan*/  mmio_rb_root ; 
 int /*<<< orphan*/  mmio_rwlock ; 
 int /*<<< orphan*/  pthread_rwlock_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
init_mem(void)
{

	RB_INIT(&mmio_rb_root);
	RB_INIT(&mmio_rb_fallback);
	pthread_rwlock_init(&mmio_rwlock, NULL);
}