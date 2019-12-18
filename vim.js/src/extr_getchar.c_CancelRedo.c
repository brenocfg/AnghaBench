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
struct TYPE_5__ {int /*<<< orphan*/ * b_next; } ;
struct TYPE_6__ {TYPE_1__ bh_first; } ;

/* Variables and functions */
 scalar_t__ NUL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  block_redo ; 
 int /*<<< orphan*/  free_buff (TYPE_2__*) ; 
 TYPE_2__ old_redobuff ; 
 scalar_t__ read_stuff (int /*<<< orphan*/ ) ; 
 TYPE_2__ redobuff ; 
 int /*<<< orphan*/  start_stuff () ; 

void
CancelRedo()
{
    if (!block_redo)
    {
	free_buff(&redobuff);
	redobuff = old_redobuff;
	old_redobuff.bh_first.b_next = NULL;
	start_stuff();
	while (read_stuff(TRUE) != NUL)
	    ;
    }
}