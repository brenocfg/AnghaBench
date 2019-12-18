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
typedef  int /*<<< orphan*/  ts_pmt_t ;
struct TYPE_3__ {struct TYPE_3__* p_extraes; scalar_t__ id; struct TYPE_3__* p_next; } ;
typedef  TYPE_1__ ts_es_t ;
typedef  int /*<<< orphan*/  es_out_t ;

/* Variables and functions */
 int /*<<< orphan*/  ES_OUT_GET_ES_STATE ; 
 int /*<<< orphan*/  es_out_Control (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int*) ; 

__attribute__((used)) static inline void HasSelectedES( es_out_t *out, const ts_es_t *p_es,
                                  const ts_pmt_t *p_pmt, bool *pb_stream_selected )
{
    for( ; p_es && !*pb_stream_selected; p_es = p_es->p_next )
    {
        if( p_es->id )
            es_out_Control( out, ES_OUT_GET_ES_STATE,
                            p_es->id, pb_stream_selected );
        HasSelectedES( out, p_es->p_extraes, p_pmt, pb_stream_selected );
    }
}