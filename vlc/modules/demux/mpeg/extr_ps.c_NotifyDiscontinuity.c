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
struct TYPE_3__ {int /*<<< orphan*/  i_next_block_flags; scalar_t__ es; } ;
typedef  TYPE_1__ ps_track_t ;
typedef  int /*<<< orphan*/  es_out_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_FLAG_DISCONTINUITY ; 
 int /*<<< orphan*/  ES_OUT_GET_ES_STATE ; 
 size_t PS_TK_COUNT ; 
 scalar_t__ VLC_SUCCESS ; 
 scalar_t__ es_out_Control (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int*) ; 

__attribute__((used)) static void NotifyDiscontinuity( ps_track_t *p_tk, es_out_t *out )
{
    bool b_selected;
    for( size_t i = 0; i < PS_TK_COUNT; i++ )
    {
        ps_track_t *tk = &p_tk[i];
        if( tk->es &&
                es_out_Control( out, ES_OUT_GET_ES_STATE, tk->es, &b_selected ) == VLC_SUCCESS
                && b_selected )
        {
            tk->i_next_block_flags |= BLOCK_FLAG_DISCONTINUITY;
        }
    }
}