#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sout_buffer_chain_t ;
struct TYPE_3__ {int /*<<< orphan*/  i_flags; struct TYPE_3__* p_next; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_FLAG_HEADER ; 
 TYPE_1__* BufferChainPeek (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void SetHeader( sout_buffer_chain_t *c,
                        int depth )
{
    block_t *p_ts = BufferChainPeek( c );
    while( depth > 0 )
    {
        p_ts = p_ts->p_next;
        depth--;
    }
    p_ts->i_flags |= BLOCK_FLAG_HEADER;
}