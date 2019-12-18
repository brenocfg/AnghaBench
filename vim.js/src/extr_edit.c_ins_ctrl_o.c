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

/* Variables and functions */
 int FALSE ; 
 scalar_t__ NUL ; 
 int REPLACE_FLAG ; 
 int State ; 
 int VREPLACE_FLAG ; 
 scalar_t__ gchar_cursor () ; 
 int ins_at_eol ; 
 char restart_edit ; 
 scalar_t__ virtual_active () ; 

__attribute__((used)) static void
ins_ctrl_o()
{
#ifdef FEAT_VREPLACE
    if (State & VREPLACE_FLAG)
	restart_edit = 'V';
    else
#endif
	if (State & REPLACE_FLAG)
	restart_edit = 'R';
    else
	restart_edit = 'I';
#ifdef FEAT_VIRTUALEDIT
    if (virtual_active())
	ins_at_eol = FALSE;	/* cursor always keeps its column */
    else
#endif
	ins_at_eol = (gchar_cursor() == NUL);
}