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
#define  if_elif 133 
#define  if_elsefalse 132 
#define  if_elsetrue 131 
#define  if_false 130 
#define  if_ignore 129 
#define  if_true 128 
 int pp_if_state () ; 
 int /*<<< orphan*/  pp_internal_error (char*,int,char*,int) ; 
 int /*<<< orphan*/  pp_push_if (int const) ; 

void pp_next_if_state(int i)
{
	switch(pp_if_state())
	{
	case if_true:
	case if_elsetrue:
		pp_push_if(i ? if_true : if_false);
		break;
	case if_false:
	case if_elsefalse:
	case if_elif:
	case if_ignore:
		pp_push_if(if_ignore);
		break;
	default:
		pp_internal_error(__FILE__, __LINE__, "Invalid pp_if_state (%d) in #{if,ifdef,ifndef} directive", (int)pp_if_state());
	}
}