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
 int INSERT ; 
 int State ; 
 int /*<<< orphan*/  add_to_input_buf (int /*<<< orphan*/ *,int) ; 
 scalar_t__ isShowing (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
warp_to_pc(
	int	 lnum)			/* line number to warp to */
{
    char	 lbuf[256];		/* build line command here */

    if (lnum > 0)
    {
	if (State & INSERT)
	    add_to_input_buf((char_u *) "\033", 1);
	if (isShowing(lnum))
	    sprintf(lbuf, "%dG", lnum);
	else
	    sprintf(lbuf, "%dz.", lnum);
	add_to_input_buf((char_u *) lbuf, strlen(lbuf));
    }
}