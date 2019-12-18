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
 unsigned long MINORBITS ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVOL_DRIVER ; 
 int /*<<< orphan*/  blk_unregister_region (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  ida_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskq_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_blkdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zvol_fini_impl () ; 
 int /*<<< orphan*/  zvol_ida ; 
 int /*<<< orphan*/  zvol_major ; 
 int /*<<< orphan*/  zvol_taskq ; 

void
zvol_fini(void)
{
	zvol_fini_impl();
	blk_unregister_region(MKDEV(zvol_major, 0), 1UL << MINORBITS);
	unregister_blkdev(zvol_major, ZVOL_DRIVER);
	taskq_destroy(zvol_taskq);
	ida_destroy(&zvol_ida);
}