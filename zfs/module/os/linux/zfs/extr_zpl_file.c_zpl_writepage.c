#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct writeback_control {int /*<<< orphan*/  sync_mode; } ;
struct page {TYPE_2__* mapping; } ;
struct TYPE_6__ {TYPE_1__* z_os; } ;
struct TYPE_5__ {int /*<<< orphan*/  host; } ;
struct TYPE_4__ {scalar_t__ os_sync; } ;

/* Variables and functions */
 TYPE_3__* ITOZSB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WB_SYNC_ALL ; 
 scalar_t__ ZFS_SYNC_ALWAYS ; 
 int zpl_putpage (struct page*,struct writeback_control*,TYPE_2__*) ; 

__attribute__((used)) static int
zpl_writepage(struct page *pp, struct writeback_control *wbc)
{
	if (ITOZSB(pp->mapping->host)->z_os->os_sync == ZFS_SYNC_ALWAYS)
		wbc->sync_mode = WB_SYNC_ALL;

	return (zpl_putpage(pp, wbc, pp->mapping));
}