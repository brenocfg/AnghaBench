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
 int /*<<< orphan*/  ppy__create_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppy__init_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ppy__load_buffer_state () ; 
 int /*<<< orphan*/  ppy_ensure_buffer_stack () ; 
 int /*<<< orphan*/  ppy_in ; 

void ppy_restart  (FILE * input_file )
{
    
	if ( ! YY_CURRENT_BUFFER ){
        ppy_ensure_buffer_stack ();
		YY_CURRENT_BUFFER_LVALUE =
            ppy__create_buffer(ppy_in,YY_BUF_SIZE );
	}

	ppy__init_buffer(YY_CURRENT_BUFFER,input_file );
	ppy__load_buffer_state( );
}