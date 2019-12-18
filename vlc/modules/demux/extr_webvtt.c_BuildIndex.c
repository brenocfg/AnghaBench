#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct index_entry_s {int dummy; } ;
struct TYPE_7__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_6__ {size_t i_count; TYPE_4__* p_array; } ;
struct TYPE_8__ {TYPE_1__ index; } ;
typedef  TYPE_3__ demux_sys_t ;
struct TYPE_9__ {int active; } ;

/* Variables and functions */
 int /*<<< orphan*/  index_Compare ; 
 int /*<<< orphan*/  qsort (TYPE_4__*,size_t,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void BuildIndex( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;

    /* Order time entries ascending, start time before end time */
    qsort( p_sys->index.p_array, p_sys->index.i_count,
           sizeof(struct index_entry_s), index_Compare );

    /* Build actives count
    TIME 3000 count 1
    TIME 14500 count 2 (1 overlap)
    TIME 16100 count 3 (2 overlaps)
    TIME 16100 count 2 (1 overlap.. because there next start == end)
    TIME 18000 count 3
    TIME 18000 count 2 */
    unsigned i_overlaps = 0;
    for( size_t i=0; i<p_sys->index.i_count; i++ )
    {
        if( p_sys->index.p_array[i].active )
            p_sys->index.p_array[i].active = ++i_overlaps;
        else
            p_sys->index.p_array[i].active = --i_overlaps;
    }
}