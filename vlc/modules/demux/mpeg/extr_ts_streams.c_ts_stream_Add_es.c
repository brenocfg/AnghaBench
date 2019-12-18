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
struct TYPE_6__ {struct TYPE_6__* p_next; struct TYPE_6__* p_extraes; } ;
typedef  TYPE_2__ ts_es_t ;

/* Variables and functions */
 scalar_t__ likely (int) ; 

void ts_stream_Add_es( ts_stream_t *p_pes, ts_es_t *p_es, bool b_extra )
{
    ts_es_t **pp_es = (b_extra && p_pes->p_es) ?  /* Ensure extra has main es */
                           &p_pes->p_es->p_extraes :
                           &p_pes->p_es;
    if( likely(!*pp_es) )
    {
        *pp_es = p_es;
    }
    else
    {
        ts_es_t *p_next = (*pp_es)->p_next;
        (*pp_es)->p_next = p_es;
        p_es->p_next = p_next;
    }
}