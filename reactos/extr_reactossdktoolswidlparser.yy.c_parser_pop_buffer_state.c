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
 scalar_t__ YY_CURRENT_BUFFER ; 
 int /*<<< orphan*/ * YY_CURRENT_BUFFER_LVALUE ; 
 int /*<<< orphan*/  parser__delete_buffer (scalar_t__) ; 
 int /*<<< orphan*/  parser__load_buffer_state () ; 
 scalar_t__ yy_buffer_stack_top ; 
 int yy_did_buffer_switch_on_eof ; 

void parser_pop_buffer_state (void)
{
    	if (!YY_CURRENT_BUFFER)
		return;

	parser__delete_buffer(YY_CURRENT_BUFFER );
	YY_CURRENT_BUFFER_LVALUE = NULL;
	if ((yy_buffer_stack_top) > 0)
		--(yy_buffer_stack_top);

	if (YY_CURRENT_BUFFER) {
		parser__load_buffer_state( );
		(yy_did_buffer_switch_on_eof) = 1;
	}
}