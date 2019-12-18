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
struct TYPE_4__ {int i_pagepos_end; int /*<<< orphan*/ * p_prev; int /*<<< orphan*/  p_next; } ;
typedef  TYPE_1__ demux_index_entry_t ;

/* Variables and functions */
 TYPE_1__* xmalloc (int) ; 

__attribute__((used)) static demux_index_entry_t *index_entry_new( void )
{
    demux_index_entry_t *idx = xmalloc( sizeof( demux_index_entry_t ) );
    if ( !idx ) return NULL;
    idx->p_next = idx->p_prev = NULL;
    idx->i_pagepos_end = -1;
    return idx;
}