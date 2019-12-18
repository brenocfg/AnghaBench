#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * b_next; } ;
struct TYPE_4__ {scalar_t__ bh_space; TYPE_1__ bh_first; TYPE_1__* bh_curr; } ;

/* Variables and functions */
 TYPE_2__ stuffbuff ; 

__attribute__((used)) static void
start_stuff()
{
    if (stuffbuff.bh_first.b_next != NULL)
    {
	stuffbuff.bh_curr = &(stuffbuff.bh_first);
	stuffbuff.bh_space = 0;
    }
}