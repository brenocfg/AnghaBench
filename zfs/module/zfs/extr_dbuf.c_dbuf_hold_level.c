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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  dnode_t ;
typedef  int /*<<< orphan*/  dmu_buf_impl_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int dbuf_hold_impl (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ **) ; 

dmu_buf_impl_t *
dbuf_hold_level(dnode_t *dn, int level, uint64_t blkid, void *tag)
{
	dmu_buf_impl_t *db;
	int err = dbuf_hold_impl(dn, level, blkid, FALSE, FALSE, tag, &db);
	return (err ? NULL : db);
}