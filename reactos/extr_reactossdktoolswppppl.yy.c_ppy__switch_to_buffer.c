#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* YY_BUFFER_STATE ;
struct TYPE_5__ {int /*<<< orphan*/  yy_n_chars; int /*<<< orphan*/ * yy_buf_pos; } ;

/* Variables and functions */
 TYPE_1__* YY_CURRENT_BUFFER ; 
 TYPE_1__* YY_CURRENT_BUFFER_LVALUE ; 
 int /*<<< orphan*/  ppy__load_buffer_state () ; 
 int /*<<< orphan*/  ppy_ensure_buffer_stack () ; 
 int /*<<< orphan*/ * yy_c_buf_p ; 
 int yy_did_buffer_switch_on_eof ; 
 int /*<<< orphan*/  yy_hold_char ; 
 int /*<<< orphan*/  yy_n_chars ; 

void ppy__switch_to_buffer  (YY_BUFFER_STATE  new_buffer )
{
    
	/* TODO. We should be able to replace this entire function body
	 * with
	 *		ppy_pop_buffer_state();
	 *		ppy_push_buffer_state(new_buffer);
     */
	ppy_ensure_buffer_stack ();
	if ( YY_CURRENT_BUFFER == new_buffer )
		return;

	if ( YY_CURRENT_BUFFER )
		{
		/* Flush out information for old buffer. */
		*(yy_c_buf_p) = (yy_hold_char);
		YY_CURRENT_BUFFER_LVALUE->yy_buf_pos = (yy_c_buf_p);
		YY_CURRENT_BUFFER_LVALUE->yy_n_chars = (yy_n_chars);
		}

	YY_CURRENT_BUFFER_LVALUE = new_buffer;
	ppy__load_buffer_state( );

	/* We don't actually know whether we did this switch during
	 * EOF (ppy_wrap()) processing, but the only time this flag
	 * is looked at is after ppy_wrap() is called, so it's safe
	 * to go ahead and always set it.
	 */
	(yy_did_buffer_switch_on_eof) = 1;
}