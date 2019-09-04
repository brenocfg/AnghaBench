#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* YY_BUFFER_STATE ;
struct TYPE_4__ {int yy_at_bol; int /*<<< orphan*/  yy_buffer_status; void** yy_ch_buf; void** yy_buf_pos; scalar_t__ yy_n_chars; } ;

/* Variables and functions */
 int /*<<< orphan*/  YY_BUFFER_NEW ; 
 TYPE_1__* YY_CURRENT_BUFFER ; 
 void* YY_END_OF_BUFFER_CHAR ; 
 int /*<<< orphan*/  ppy__load_buffer_state () ; 

void ppy__flush_buffer (YY_BUFFER_STATE  b )
{
    	if ( ! b )
		return;

	b->yy_n_chars = 0;

	/* We always need two end-of-buffer characters.  The first causes
	 * a transition to the end-of-buffer state.  The second causes
	 * a jam in that state.
	 */
	b->yy_ch_buf[0] = YY_END_OF_BUFFER_CHAR;
	b->yy_ch_buf[1] = YY_END_OF_BUFFER_CHAR;

	b->yy_buf_pos = &b->yy_ch_buf[0];

	b->yy_at_bol = 1;
	b->yy_buffer_status = YY_BUFFER_NEW;

	if ( b == YY_CURRENT_BUFFER )
		ppy__load_buffer_state( );
}