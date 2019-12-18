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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  drc_os; int /*<<< orphan*/  drc_ignore_objlist; } ;
typedef  TYPE_1__ dmu_recv_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZIO_PRIORITY_SYNC_READ ; 
 int /*<<< orphan*/  dmu_prefetch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  objlist_exists (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
receive_read_prefetch(dmu_recv_cookie_t *drc, uint64_t object, uint64_t offset,
    uint64_t length)
{
	if (!objlist_exists(drc->drc_ignore_objlist, object)) {
		dmu_prefetch(drc->drc_os, object, 1, offset, length,
		    ZIO_PRIORITY_SYNC_READ);
	}
}