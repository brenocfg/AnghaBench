#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  lnum; } ;
struct TYPE_6__ {TYPE_1__ w_cursor; } ;

/* Variables and functions */
 int DONE_ACTION ; 
 int DONE_NOTHING ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  checkupdate (TYPE_2__*) ; 
 TYPE_2__* curwin ; 
 scalar_t__ hasAnyFolding (TYPE_2__*) ; 
 int /*<<< orphan*/  setManualFold (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

void
foldOpenCursor()
{
    int		done;

    checkupdate(curwin);
    if (hasAnyFolding(curwin))
	for (;;)
	{
	    done = DONE_NOTHING;
	    (void)setManualFold(curwin->w_cursor.lnum, TRUE, FALSE, &done);
	    if (!(done & DONE_ACTION))
		break;
	}
}