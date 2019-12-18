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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  YY_BUF_SIZE ; 
 int /*<<< orphan*/  YY_CURRENT_BUFFER ; 
 int /*<<< orphan*/  YY_CURRENT_BUFFER_LVALUE ; 
 int /*<<< orphan*/  parser__create_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parser__init_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parser__load_buffer_state () ; 
 int /*<<< orphan*/  parser_ensure_buffer_stack () ; 
 int /*<<< orphan*/  parser_in ; 

void parser_restart  (FILE * input_file )
{
    
	if ( ! YY_CURRENT_BUFFER ){
        parser_ensure_buffer_stack ();
		YY_CURRENT_BUFFER_LVALUE =
            parser__create_buffer(parser_in,YY_BUF_SIZE );
	}

	parser__init_buffer(YY_CURRENT_BUFFER,input_file );
	parser__load_buffer_state( );
}