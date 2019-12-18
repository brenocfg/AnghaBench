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
 int FALSE ; 
 int TRUE ; 
 scalar_t__ mch_is_hard_link (int /*<<< orphan*/ *) ; 
 scalar_t__ mch_is_symbolic_link (int /*<<< orphan*/ *) ; 

int
mch_is_linked(char_u *fname)
{
    if (mch_is_hard_link(fname) || mch_is_symbolic_link(fname))
	return TRUE;
    return FALSE;
}