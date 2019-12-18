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
struct TYPE_4__ {int active; int /*<<< orphan*/  (* changefunc ) (int) ;int /*<<< orphan*/  text; } ;
struct TYPE_3__ {scalar_t__* batpath; int /*<<< orphan*/  batname; } ;

/* Variables and functions */
 scalar_t__ NUL ; 
 int TARGET_COUNT ; 
 int /*<<< orphan*/  bat_text_no ; 
 int /*<<< orphan*/  bat_text_yes ; 
 int /*<<< orphan*/  change_bat_choice (int) ; 
 TYPE_2__* choices ; 
 int /*<<< orphan*/  set_bat_text (int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (scalar_t__*,scalar_t__*) ; 
 TYPE_1__* targets ; 

__attribute__((used)) static void
change_main_bat_choice(int idx)
{
    int		i;

    /* let the user select a default directory or NONE */
    change_bat_choice(idx);

    if (targets[0].batpath[0] != NUL)
	choices[idx].text = bat_text_yes;
    else
	choices[idx].text = bat_text_no;

    /* update the individual batch file selections */
    for (i = 1; i < TARGET_COUNT; ++i)
    {
	/* Only make it active when the first item has a path and the vim.exe
	 * or gvim.exe exists (there is a changefunc then). */
	if (targets[0].batpath[0] != NUL
		&& choices[idx + i].changefunc != NULL)
	{
	    choices[idx + i].active = 1;
	    if (choices[idx + i].changefunc == change_bat_choice
		    && targets[i].batpath[0] != NUL)
	    {
		strcpy(targets[i].batpath, targets[0].batpath);
		set_bat_text(idx + i, targets[i].batpath, targets[i].batname);
	    }
	}
	else
	    choices[idx + i].active = 0;
    }
}