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
struct TYPE_5__ {int* pi_v_cadence_pos; int* pi_s_cadence_pos; int* pi_cadence_pos_history; scalar_t__* pb_s_reliable; scalar_t__* pb_v_reliable; } ;
typedef  TYPE_1__ ivtc_sys_t ;
struct TYPE_6__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ filter_t ;
struct TYPE_7__ {TYPE_1__ ivtc; } ;
typedef  TYPE_3__ filter_sys_t ;

/* Variables and functions */
 int CADENCE_POS_INVALID ; 
 size_t IVTC_LATEST ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void IVTCCadenceDetectFinalize( filter_t *p_filter )
{
    assert( p_filter != NULL );

    filter_sys_t *p_sys = p_filter->p_sys;
    ivtc_sys_t *p_ivtc  = &p_sys->ivtc;

    /* In practice "vektor" is more reliable than "scores", but it may
       take longer to lock on. Thus, we prefer "vektor" if its reliable bit
       is set, then "scores", and finally just give up.

       For progressive sequences, "vektor" outputs "3, -, 3, -, ...",
       because the repeated progressive position is an inconsistent prediction.
       In this case, "scores" fills in the blanks. (This particular task
       could also be done without another cadence detector, by just
       detecting the alternating pattern of "3" and no result.)
    */
    int pos = CADENCE_POS_INVALID;
    if( p_ivtc->pb_v_reliable[IVTC_LATEST] )
        pos = p_ivtc->pi_v_cadence_pos[IVTC_LATEST];
    else if( p_ivtc->pb_s_reliable[IVTC_LATEST] )
        pos = p_ivtc->pi_s_cadence_pos[IVTC_LATEST];
    p_ivtc->pi_cadence_pos_history[IVTC_LATEST] = pos;
}