#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ft_tid; } ;
typedef  TYPE_1__ fmd_timer_t ;
typedef  int /*<<< orphan*/  fmd_hdl_t ;

/* Variables and functions */
 int /*<<< orphan*/  fmd_hdl_debug (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmd_hdl_free (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  timer_delete (int /*<<< orphan*/ ) ; 

void
fmd_timer_remove(fmd_hdl_t *hdl, fmd_timer_t *ftp)
{
	fmd_hdl_debug(hdl, "removing timer (%p)", ftp->ft_tid);

	timer_delete(ftp->ft_tid);

	fmd_hdl_free(hdl, ftp, sizeof (fmd_timer_t));
}