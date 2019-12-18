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
struct TYPE_5__ {int* pi_motion; int* pb_s_reliable; int* pb_v_reliable; int* pb_all_progressives; scalar_t__* pi_scores; scalar_t__* pi_bot_rep; scalar_t__* pi_top_rep; void** pi_cadence_pos_history; int /*<<< orphan*/ * pi_v_raw; void** pi_v_cadence_pos; void** pi_s_cadence_pos; } ;
typedef  TYPE_1__ ivtc_sys_t ;
struct TYPE_6__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ filter_t ;
struct TYPE_7__ {TYPE_1__ ivtc; } ;
typedef  TYPE_3__ filter_sys_t ;

/* Variables and functions */
 void* CADENCE_POS_INVALID ; 
 size_t FIELD_PAIR_TCBC ; 
 size_t FIELD_PAIR_TCBN ; 
 size_t FIELD_PAIR_TCBP ; 
 size_t FIELD_PAIR_TNBC ; 
 size_t FIELD_PAIR_TNBN ; 
 size_t FIELD_PAIR_TPBC ; 
 size_t FIELD_PAIR_TPBP ; 
 int IVTC_DETECTION_HISTORY_SIZE ; 
 size_t IVTC_LATEST ; 
 int /*<<< orphan*/  VEKTOR_CADENCE_POS_ALL ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void IVTCFrameInit( filter_t *p_filter )
{
    assert( p_filter != NULL );

    filter_sys_t *p_sys = p_filter->p_sys;
    ivtc_sys_t *p_ivtc  = &p_sys->ivtc;

    /* Slide detector histories */
    for( int i = 1; i < IVTC_DETECTION_HISTORY_SIZE; i++ )
    {
        p_ivtc->pi_top_rep[i-1] = p_ivtc->pi_top_rep[i];
        p_ivtc->pi_bot_rep[i-1] = p_ivtc->pi_bot_rep[i];
        p_ivtc->pi_motion[i-1]  = p_ivtc->pi_motion[i];

        p_ivtc->pi_s_cadence_pos[i-1] = p_ivtc->pi_s_cadence_pos[i];
        p_ivtc->pb_s_reliable[i-1]    = p_ivtc->pb_s_reliable[i];
        p_ivtc->pi_v_cadence_pos[i-1] = p_ivtc->pi_v_cadence_pos[i];
        p_ivtc->pi_v_raw[i-1]         = p_ivtc->pi_v_raw[i];
        p_ivtc->pb_v_reliable[i-1]    = p_ivtc->pb_v_reliable[i];

        p_ivtc->pi_cadence_pos_history[i-1]
                                      = p_ivtc->pi_cadence_pos_history[i];

        p_ivtc->pb_all_progressives[i-1] = p_ivtc->pb_all_progressives[i];
    }
    /* The latest position has not been detected yet. */
    p_ivtc->pi_s_cadence_pos[IVTC_LATEST] = CADENCE_POS_INVALID;
    p_ivtc->pb_s_reliable[IVTC_LATEST]    = false;
    p_ivtc->pi_v_cadence_pos[IVTC_LATEST] = CADENCE_POS_INVALID;
    p_ivtc->pi_v_raw[IVTC_LATEST]         = VEKTOR_CADENCE_POS_ALL;
    p_ivtc->pb_v_reliable[IVTC_LATEST]    = false;
    p_ivtc->pi_cadence_pos_history[IVTC_LATEST] = CADENCE_POS_INVALID;
    p_ivtc->pi_top_rep[IVTC_LATEST] =  0;
    p_ivtc->pi_bot_rep[IVTC_LATEST] =  0;
    p_ivtc->pi_motion[IVTC_LATEST]  = -1;
    p_ivtc->pb_all_progressives[IVTC_LATEST] = false;

    /* Slide history of field pair interlace scores */
    p_ivtc->pi_scores[FIELD_PAIR_TPBP] = p_ivtc->pi_scores[FIELD_PAIR_TCBC];
    p_ivtc->pi_scores[FIELD_PAIR_TPBC] = p_ivtc->pi_scores[FIELD_PAIR_TCBN];
    p_ivtc->pi_scores[FIELD_PAIR_TCBP] = p_ivtc->pi_scores[FIELD_PAIR_TNBC];
    p_ivtc->pi_scores[FIELD_PAIR_TCBC] = p_ivtc->pi_scores[FIELD_PAIR_TNBN];
    /* These have not been detected yet */
    p_ivtc->pi_scores[FIELD_PAIR_TCBN] = 0;
    p_ivtc->pi_scores[FIELD_PAIR_TNBC] = 0;
    p_ivtc->pi_scores[FIELD_PAIR_TNBN] = 0;
}