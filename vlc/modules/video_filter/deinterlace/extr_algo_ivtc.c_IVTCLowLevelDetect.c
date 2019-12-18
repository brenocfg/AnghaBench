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
typedef  int /*<<< orphan*/  picture_t ;
struct TYPE_7__ {int* pi_motion; int* pi_top_rep; int* pi_bot_rep; void** pi_scores; } ;
typedef  TYPE_2__ ivtc_sys_t ;
struct TYPE_8__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ filter_t ;
struct TYPE_6__ {int /*<<< orphan*/ ** pp_history; } ;
struct TYPE_9__ {TYPE_1__ context; TYPE_2__ ivtc; } ;
typedef  TYPE_4__ filter_sys_t ;

/* Variables and functions */
 void* CalculateInterlaceScore (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int EstimateNumBlocksWithMotion (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*) ; 
 size_t FIELD_PAIR_TCBN ; 
 size_t FIELD_PAIR_TNBC ; 
 size_t FIELD_PAIR_TNBN ; 
 size_t IVTC_LATEST ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void IVTCLowLevelDetect( filter_t *p_filter )
{
    assert( p_filter != NULL );

    filter_sys_t *p_sys = p_filter->p_sys;
    ivtc_sys_t *p_ivtc  = &p_sys->ivtc;
    picture_t *p_curr = p_sys->context.pp_history[1];
    picture_t *p_next = p_sys->context.pp_history[2];

    assert( p_next != NULL );
    assert( p_curr != NULL );

    /* Compute interlace scores for TNBN, TNBC and TCBN.
        Note that p_next contains TNBN. */
    p_ivtc->pi_scores[FIELD_PAIR_TNBN] = CalculateInterlaceScore( p_next,
                                                                  p_next );
    p_ivtc->pi_scores[FIELD_PAIR_TNBC] = CalculateInterlaceScore( p_next,
                                                                  p_curr );
    p_ivtc->pi_scores[FIELD_PAIR_TCBN] = CalculateInterlaceScore( p_curr,
                                                                  p_next );

    int i_top = 0, i_bot = 0;
    int i_motion = EstimateNumBlocksWithMotion(p_curr, p_next, &i_top, &i_bot);
    p_ivtc->pi_motion[IVTC_LATEST] = i_motion;

    /* If one field changes "clearly more" than the other, we know the
       less changed one is a likely duplicate.

       Threshold 1/2 is too low for some scenes (e.g. pan of the space junk
       at beginning of The Third ep. 1, right after the OP). Thus, we use 2/3,
       which seems to work.
    */
    p_ivtc->pi_top_rep[IVTC_LATEST] = (i_top <= 2*i_bot/3);
    p_ivtc->pi_bot_rep[IVTC_LATEST] = (i_bot <= 2*i_top/3);
}