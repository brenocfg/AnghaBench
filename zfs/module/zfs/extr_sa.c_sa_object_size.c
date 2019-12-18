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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
struct TYPE_3__ {int /*<<< orphan*/  sa_bonus; } ;
typedef  TYPE_1__ sa_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  dmu_object_size_from_db (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
sa_object_size(sa_handle_t *hdl, uint32_t *blksize, u_longlong_t *nblocks)
{
	dmu_object_size_from_db(hdl->sa_bonus,
	    blksize, nblocks);
}