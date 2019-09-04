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
struct TYPE_4__ {int /*<<< orphan*/  unum; int /*<<< orphan*/ * txt; } ;
typedef  TYPE_1__ loc_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  safe_free (int /*<<< orphan*/ ) ; 

void free_loc_cmd(loc_cmd* lcmd)
{
	if (lcmd == NULL)
		return;
	safe_free(lcmd->txt[0]);
	safe_free(lcmd->txt[1]);
	safe_free(lcmd->unum);
	free(lcmd);
}