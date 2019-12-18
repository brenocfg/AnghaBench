#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_12__ {int i_size; TYPE_3__** p_elems; } ;
struct TYPE_13__ {TYPE_4__ e_streams; } ;
typedef  TYPE_5__ ts_pmt_t ;
struct TYPE_14__ {scalar_t__ i_sl_es_id; } ;
typedef  TYPE_6__ ts_es_t ;
struct TYPE_10__ {TYPE_1__* p_stream; } ;
struct TYPE_11__ {TYPE_2__ u; } ;
struct TYPE_9__ {TYPE_6__* p_es; } ;

/* Variables and functions */

__attribute__((used)) static ts_es_t * GetPMTESBySLEsId( ts_pmt_t *pmt, uint16_t i_sl_es_id )
{
    for( int i=0; i< pmt->e_streams.i_size; i++ )
    {
        ts_es_t *p_es = pmt->e_streams.p_elems[i]->u.p_stream->p_es;
        if( p_es->i_sl_es_id == i_sl_es_id )
            return p_es;
    }
    return NULL;
}