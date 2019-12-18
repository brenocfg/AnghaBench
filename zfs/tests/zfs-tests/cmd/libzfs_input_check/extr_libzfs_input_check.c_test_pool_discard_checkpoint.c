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
 int /*<<< orphan*/  IOC_INPUT_TEST (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ZFS_ERR_CHECKPOINT_EXISTS ; 
 int /*<<< orphan*/  ZFS_IOC_POOL_DISCARD_CHECKPOINT ; 
 int lzc_pool_checkpoint (char const*) ; 

__attribute__((used)) static void
test_pool_discard_checkpoint(const char *pool)
{
	int err = lzc_pool_checkpoint(pool);
	if (err == 0 || err == ZFS_ERR_CHECKPOINT_EXISTS)
		IOC_INPUT_TEST(ZFS_IOC_POOL_DISCARD_CHECKPOINT, pool, NULL,
		    NULL, 0);
}