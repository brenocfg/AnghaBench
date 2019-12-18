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
typedef  int /*<<< orphan*/  pp_if_state_t ;

/* Variables and functions */
 int /*<<< orphan*/ * if_stack ; 
 int if_stack_idx ; 
 int /*<<< orphan*/  if_true ; 

pp_if_state_t pp_if_state(void)
{
	if(!if_stack_idx)
		return if_true;
	else
		return if_stack[if_stack_idx-1];
}