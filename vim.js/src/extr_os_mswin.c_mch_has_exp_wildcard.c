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
typedef  char char_u ;

/* Variables and functions */
 int FALSE ; 
 char NUL ; 
 int TRUE ; 
 int /*<<< orphan*/  mb_ptr_adv (char*) ; 
 int /*<<< orphan*/ * vim_strchr (char*,char) ; 

int
mch_has_exp_wildcard(char_u *p)
{
    for ( ; *p; mb_ptr_adv(p))
    {
	if (vim_strchr((char_u *)"?*[", *p) != NULL
		|| (*p == '~' && p[1] != NUL))
	    return TRUE;
    }
    return FALSE;
}