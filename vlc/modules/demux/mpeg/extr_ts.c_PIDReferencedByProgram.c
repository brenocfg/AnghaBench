#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_6__ {int i_size; TYPE_1__** p_elems; } ;
struct TYPE_7__ {TYPE_2__ e_streams; } ;
typedef  TYPE_3__ ts_pmt_t ;
struct TYPE_5__ {scalar_t__ i_pid; } ;

/* Variables and functions */

__attribute__((used)) static bool PIDReferencedByProgram( const ts_pmt_t *p_pmt, uint16_t i_pid )
{
    for(int i=0; i<p_pmt->e_streams.i_size; i++)
        if( p_pmt->e_streams.p_elems[i]->i_pid == i_pid )
            return true;

    return false;
}