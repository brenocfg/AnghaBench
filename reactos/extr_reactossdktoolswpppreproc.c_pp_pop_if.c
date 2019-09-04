#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t pp_if_state_t ;
struct TYPE_2__ {char* input; int line_number; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int,char*,int,char*,int) ; 
#define  if_elif 133 
#define  if_elsefalse 132 
#define  if_elsetrue 131 
 size_t if_error ; 
#define  if_false 130 
#define  if_ignore 129 
 size_t* if_stack ; 
 int if_stack_idx ; 
#define  if_true 128 
 scalar_t__ pp_flex_debug ; 
 size_t pp_if_state () ; 
 char** pp_if_state_str ; 
 int /*<<< orphan*/  pp_internal_error (char*,int,char*,int) ; 
 int /*<<< orphan*/  pp_pop_ignore_state () ; 
 TYPE_1__ pp_status ; 
 int /*<<< orphan*/  ppy_error (char*) ; 
 int /*<<< orphan*/  stderr ; 

pp_if_state_t pp_pop_if(void)
{
	if(if_stack_idx <= 0)
	{
		ppy_error("#{endif,else,elif} without #{if,ifdef,ifndef} (#if-stack underflow)");
		return if_error;
	}

	switch(pp_if_state())
	{
	case if_true:
	case if_elsetrue:
		break;
	case if_false:
	case if_elsefalse:
	case if_elif:
	case if_ignore:
		pp_pop_ignore_state();
		break;
	default:
		pp_internal_error(__FILE__, __LINE__, "Invalid pp_if_state (%d)", (int)pp_if_state());
	}

	if(pp_flex_debug)
		fprintf(stderr, "Pop if %s:%d: %s(%d) -> %s(%d)\n",
				pp_status.input,
				pp_status.line_number,
				pp_if_state_str[pp_if_state()],
				if_stack_idx,
				pp_if_state_str[if_stack[if_stack_idx <= 1 ? if_true : if_stack_idx-2]],
				if_stack_idx-1);

	return if_stack[--if_stack_idx];
}