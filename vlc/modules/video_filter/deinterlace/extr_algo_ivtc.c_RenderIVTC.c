#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  picture_t ;
struct TYPE_15__ {int* pi_scores; int* pi_final_scores; } ;
typedef  TYPE_2__ ivtc_sys_t ;
struct TYPE_16__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ filter_t ;
struct TYPE_14__ {int /*<<< orphan*/ ** pp_history; } ;
struct TYPE_17__ {TYPE_1__ context; TYPE_2__ ivtc; } ;
typedef  TYPE_4__ filter_sys_t ;

/* Variables and functions */
 int CalculateInterlaceScore (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t FIELD_PAIR_TNBN ; 
 int /*<<< orphan*/  IVTCCadenceAnalyze (TYPE_3__*) ; 
 int /*<<< orphan*/  IVTCCadenceDetectAlgoScores (TYPE_3__*) ; 
 int /*<<< orphan*/  IVTCCadenceDetectAlgoVektor (TYPE_3__*) ; 
 int /*<<< orphan*/  IVTCCadenceDetectFinalize (TYPE_3__*) ; 
 int /*<<< orphan*/  IVTCFrameInit (TYPE_3__*) ; 
 int /*<<< orphan*/  IVTCLowLevelDetect (TYPE_3__*) ; 
 int IVTCOutputOrDropFrame (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IVTCSoftTelecineDetect (TYPE_3__*) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  picture_Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int RenderIVTC( filter_t *p_filter, picture_t *p_dst, picture_t *p_pic )
{
    VLC_UNUSED(p_pic);
    assert( p_filter != NULL );
    assert( p_dst != NULL );

    filter_sys_t *p_sys = p_filter->p_sys;
    ivtc_sys_t *p_ivtc  = &p_sys->ivtc;

    picture_t *p_prev = p_sys->context.pp_history[0];
    picture_t *p_curr = p_sys->context.pp_history[1];
    picture_t *p_next = p_sys->context.pp_history[2];

    /* If the history mechanism has failed, we have nothing to do. */
    if( !p_next )
        return VLC_EGENERIC;

    /* Slide algorithm-specific histories */
    IVTCFrameInit( p_filter );

    /* Filter if we have all the pictures we need.
       Note that we always have p_next at this point. */
    if( p_prev && p_curr )
    {
        /* Update raw data for motion, field repeats, interlace scores... */
        IVTCLowLevelDetect( p_filter );

        /* Detect soft telecine.

           Enter/exit IVTC_MODE_TELECINED_NTSC_SOFT when needed.
        */
        IVTCSoftTelecineDetect( p_filter );

        /* Detect hard telecine.

           Enter/exit IVTC_MODE_TELECINED_NTSC_HARD when needed.

           If we happen to be running in IVTC_MODE_TELECINED_NTSC_SOFT,
           we nevertheless let the algorithms see for themselves that
           the stream is progressive. This doesn't break anything,
           and this way the full filter state gets updated at each frame.

           See the individual function docs for details.
        */
        IVTCCadenceDetectAlgoScores( p_filter );
        IVTCCadenceDetectAlgoVektor( p_filter );
        IVTCCadenceDetectFinalize( p_filter ); /* pick winner */
        IVTCCadenceAnalyze( p_filter ); /* update filter state */

        /* Now we can... */
        bool b_have_output_frame = IVTCOutputOrDropFrame( p_filter, p_dst );

        if( b_have_output_frame )
            return VLC_SUCCESS;
        else
            return VLC_EGENERIC; /* Signal the caller not to expect a frame */
    }
    else if( !p_prev && !p_curr ) /* first frame */
    {
        /* Render the first frame as-is, so that a picture appears immediately.

           We will also do some init for the filter. This score will become
           TPBP by the time the actual filter starts. Note that the sliding of
           final scores only starts when the filter has started (third frame).
        */
        int i_score = CalculateInterlaceScore( p_next, p_next );
        p_ivtc->pi_scores[FIELD_PAIR_TNBN] = i_score;
        p_ivtc->pi_final_scores[0]         = i_score;

        picture_Copy( p_dst, p_next );
        return VLC_SUCCESS;
    }
    else /* second frame */
    {
        /* If the history sliding mechanism works correctly,
           the only remaining possibility is that: */
        assert( p_curr && !p_prev );

        /* We need three frames for the cadence detector to work, so we just
           do some init for the detector and pass the frame through.
           Passthrough for second frame, too, works better than drop
           for some still-image DVD menus.

           Now that we have two frames, we can run a full IVTCLowLevelDetect().

           The interlace scores from here will become TCBC, TCBP and TPBC
           when the filter starts. The score for the current TCBC has already
           been computed at the first frame, and slid into place at the start
           of this frame (by IVTCFrameInit()).
        */
        IVTCLowLevelDetect( p_filter );

        /* Note that the sliding mechanism for output scores only starts
           when the actual filter does.
        */
        p_ivtc->pi_final_scores[1] = p_ivtc->pi_scores[FIELD_PAIR_TNBN];

        picture_Copy( p_dst, p_next );
        return VLC_SUCCESS;
    }
}