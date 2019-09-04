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
 int /*<<< orphan*/  parser_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parser_pop_buffer_state () ; 
 int /*<<< orphan*/ * yy_buffer_stack ; 
 int /*<<< orphan*/  yy_init_globals () ; 
 int /*<<< orphan*/ * yy_start_stack ; 

int parser_lex_destroy  (void)
{
    
    /* Pop the buffer stack, destroying each element. */
	while(YY_CURRENT_BUFFER){
		parser__delete_buffer(YY_CURRENT_BUFFER  );
		YY_CURRENT_BUFFER_LVALUE = NULL;
		parser_pop_buffer_state();
	}

	/* Destroy the stack itself. */
	parser_free((yy_buffer_stack) );
	(yy_buffer_stack) = NULL;

    /* Destroy the start condition stack. */
        parser_free((yy_start_stack)  );
        (yy_start_stack) = NULL;

    /* Reset the globals. This is important in a non-reentrant scanner so the next time
     * parser_lex() is called, initialization will occur. */
    yy_init_globals( );

    return 0;
}