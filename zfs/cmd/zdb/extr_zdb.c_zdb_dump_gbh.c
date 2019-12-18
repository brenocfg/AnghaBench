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
typedef  int /*<<< orphan*/  blkptr_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPA_GBH_NBLKPTRS ; 
 int /*<<< orphan*/  zdb_dump_indirect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
zdb_dump_gbh(void *buf, int flags)
{
	zdb_dump_indirect((blkptr_t *)buf, SPA_GBH_NBLKPTRS, flags);
}