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
 int /*<<< orphan*/  ppy__delete_buffer (scalar_t__) ; 
 int /*<<< orphan*/  ppy_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ppy_pop_buffer_state () ; 
 int /*<<< orphan*/ * yy_buffer_stack ; 
 int /*<<< orphan*/  yy_init_globals () ; 
 int /*<<< orphan*/ * yy_start_stack ; 

int ppy_lex_destroy  (void)
{
    
    /* Pop the buffer stack, destroying each element. */
	while(YY_CURRENT_BUFFER){
		ppy__delete_buffer(YY_CURRENT_BUFFER  );
		YY_CURRENT_BUFFER_LVALUE = NULL;
		ppy_pop_buffer_state();
	}

	/* Destroy the stack itself. */
	ppy_free((yy_buffer_stack) );
	(yy_buffer_stack) = NULL;

    /* Destroy the start condition stack. */
        ppy_free((yy_start_stack)  );
        (yy_start_stack) = NULL;

    /* Reset the globals. This is important in a non-reentrant scanner so the next time
     * ppy_lex() is called, initialization will occur. */
    yy_init_globals( );

    return 0;
}