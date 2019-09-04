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
struct yy_buffer_state {int dummy; } ;
typedef  TYPE_1__* YY_BUFFER_STATE ;
struct TYPE_4__ {int yy_buf_size; char* yy_ch_buf; int yy_is_our_buffer; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  YY_FATAL_ERROR (char*) ; 
 int /*<<< orphan*/  parser__init_buffer (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ parser_alloc (int) ; 

YY_BUFFER_STATE parser__create_buffer  (FILE * file, int  size )
{
	YY_BUFFER_STATE b;
    
	b = (YY_BUFFER_STATE) parser_alloc(sizeof( struct yy_buffer_state )  );
	if ( ! b )
		YY_FATAL_ERROR( "out of dynamic memory in parser__create_buffer()" );

	b->yy_buf_size = size;

	/* yy_ch_buf has to be 2 characters longer than the size given because
	 * we need to put in 2 end-of-buffer characters.
	 */
	b->yy_ch_buf = (char *) parser_alloc(b->yy_buf_size + 2  );
	if ( ! b->yy_ch_buf )
		YY_FATAL_ERROR( "out of dynamic memory in parser__create_buffer()" );

	b->yy_is_our_buffer = 1;

	parser__init_buffer(b,file );

	return b;
}