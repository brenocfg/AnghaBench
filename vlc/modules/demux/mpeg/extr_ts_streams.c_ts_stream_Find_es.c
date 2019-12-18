#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* p_es; } ;
typedef  TYPE_1__ ts_stream_t ;
typedef  int /*<<< orphan*/  ts_pmt_t ;
struct TYPE_6__ {int /*<<< orphan*/  const* p_program; struct TYPE_6__* p_next; } ;
typedef  TYPE_2__ ts_es_t ;

/* Variables and functions */

ts_es_t * ts_stream_Find_es( ts_stream_t *p_pes, const ts_pmt_t *p_pmt )
{
    for( ts_es_t *p_es = p_pes->p_es; p_es; p_es = p_es->p_next )
    {
        if( p_es->p_program == p_pmt )
            return p_es;
    }
    return NULL;
}