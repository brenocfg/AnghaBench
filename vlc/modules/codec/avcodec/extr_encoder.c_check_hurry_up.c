#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
typedef  int /*<<< orphan*/  encoder_t ;
struct TYPE_7__ {scalar_t__ b_trellis; TYPE_1__* p_context; int /*<<< orphan*/  i_hq; } ;
typedef  TYPE_2__ encoder_sys_t ;
struct TYPE_8__ {int /*<<< orphan*/  pict_type; int /*<<< orphan*/  pts; } ;
struct TYPE_6__ {scalar_t__ trellis; int /*<<< orphan*/  mb_decision; } ;
typedef  TYPE_3__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  AV_PICTURE_TYPE_P ; 
 int /*<<< orphan*/  FF_MB_DECISION_SIMPLE ; 
 scalar_t__ FROM_AV_TS (int /*<<< orphan*/ ) ; 
 scalar_t__ HURRY_UP_GUARD1 ; 
 scalar_t__ HURRY_UP_GUARD2 ; 
 scalar_t__ HURRY_UP_GUARD3 ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ vlc_tick_now () ; 

__attribute__((used)) static void check_hurry_up( encoder_sys_t *p_sys, AVFrame *frame, encoder_t *p_enc )
{
    vlc_tick_t current_date = vlc_tick_now();

    if ( current_date + HURRY_UP_GUARD3 > FROM_AV_TS(frame->pts) )
    {
        p_sys->p_context->mb_decision = FF_MB_DECISION_SIMPLE;
        p_sys->p_context->trellis = 0;
        msg_Dbg( p_enc, "hurry up mode 3" );
    }
    else
    {
        p_sys->p_context->mb_decision = p_sys->i_hq;

        if ( current_date + HURRY_UP_GUARD2 > FROM_AV_TS(frame->pts) )
        {
            p_sys->p_context->trellis = 0;
            msg_Dbg( p_enc, "hurry up mode 2" );
        }
        else
        {
            p_sys->p_context->trellis = p_sys->b_trellis;
        }
    }

    if ( current_date + HURRY_UP_GUARD1 > FROM_AV_TS(frame->pts) )
    {
        frame->pict_type = AV_PICTURE_TYPE_P;
        /* msg_Dbg( p_enc, "hurry up mode 1 %lld", current_date + HURRY_UP_GUARD1 - frame.pts ); */
    }
}