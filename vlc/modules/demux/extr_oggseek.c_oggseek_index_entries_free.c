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
struct TYPE_4__ {struct TYPE_4__* p_next; } ;
typedef  TYPE_1__ demux_index_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void oggseek_index_entries_free ( demux_index_entry_t *idx )
{
    demux_index_entry_t *idx_next;

    while ( idx != NULL )
    {
        idx_next = idx->p_next;
        free( idx );
        idx = idx_next;
    }
}