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
struct TYPE_2__ {int /*<<< orphan*/  line_number; int /*<<< orphan*/  input_name; scalar_t__ temp_name; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  YY_CURRENT_BUFFER ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 TYPE_1__* import_stack ; 
 int import_stack_ptr ; 
 int /*<<< orphan*/  input_name ; 
 int /*<<< orphan*/  line_number ; 
 int /*<<< orphan*/  parser__delete_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parser__switch_to_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parser_in ; 
 scalar_t__ temp_name ; 
 int /*<<< orphan*/  unlink (scalar_t__) ; 

void pop_import(void)
{
	int ptr = import_stack_ptr-1;

	fclose(parser_in);
	parser__delete_buffer(YY_CURRENT_BUFFER );
	parser__switch_to_buffer(import_stack[ptr].state );
	if (temp_name) {
		unlink(temp_name);
		free(temp_name);
	}
	temp_name = import_stack[ptr].temp_name;
	input_name = import_stack[ptr].input_name;
	line_number = import_stack[ptr].line_number;
	import_stack_ptr--;
}