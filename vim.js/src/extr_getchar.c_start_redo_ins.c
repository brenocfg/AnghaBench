#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  char_u ;

/* Variables and functions */
 int FAIL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NL_STR ; 
 int NUL ; 
 int OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  block_redo ; 
 int /*<<< orphan*/  copy_redo (int /*<<< orphan*/ ) ; 
 int read_redo (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_stuff () ; 
 int /*<<< orphan*/  stuffReadbuff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vim_strchr (int /*<<< orphan*/ *,int) ; 

int
start_redo_ins()
{
    int	    c;

    if (read_redo(TRUE, FALSE) == FAIL)
	return FAIL;
    start_stuff();

    /* skip the count and the command character */
    while ((c = read_redo(FALSE, FALSE)) != NUL)
    {
	if (vim_strchr((char_u *)"AaIiRrOo", c) != NULL)
	{
	    if (c == 'O' || c == 'o')
		stuffReadbuff(NL_STR);
	    break;
	}
    }

    /* copy the typed text from the redo buffer into the stuff buffer */
    copy_redo(FALSE);
    block_redo = TRUE;
    return OK;
}