#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  length; } ;
struct TYPE_6__ {TYPE_1__ y; } ;
struct TYPE_7__ {TYPE_2__ x; int /*<<< orphan*/  width; } ;
typedef  TYPE_3__ TT_MODE ;

/* Variables and functions */
 int /*<<< orphan*/  Columns ; 
 int OK ; 
 int /*<<< orphan*/  Rows ; 
 TYPE_3__ get_tty () ; 

int
mch_get_shellsize(void)
{
    TT_MODE	tmode;

    tmode = get_tty();			/* get size from VMS	*/
    Columns = tmode.width;
    Rows = tmode.x.y.length;
    return OK;
}