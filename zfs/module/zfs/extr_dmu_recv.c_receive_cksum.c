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
struct TYPE_3__ {int /*<<< orphan*/  drc_cksum; scalar_t__ drc_byteswap; } ;
typedef  TYPE_1__ dmu_recv_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  fletcher_4_incremental_byteswap (void*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fletcher_4_incremental_native (void*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
receive_cksum(dmu_recv_cookie_t *drc, int len, void *buf)
{
	if (drc->drc_byteswap) {
		(void) fletcher_4_incremental_byteswap(buf, len,
		    &drc->drc_cksum);
	} else {
		(void) fletcher_4_incremental_native(buf, len, &drc->drc_cksum);
	}
}