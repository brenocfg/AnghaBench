#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int b_top_field_first; } ;
typedef  TYPE_2__ picture_t ;
struct TYPE_9__ {int* pi_top_rep; int* pi_bot_rep; int* pi_v_raw; int* pb_v_reliable; scalar_t__* pi_v_cadence_pos; } ;
typedef  TYPE_3__ ivtc_sys_t ;
typedef  scalar_t__ ivtc_cadence_pos ;
struct TYPE_10__ {TYPE_5__* p_sys; } ;
typedef  TYPE_4__ filter_t ;
struct TYPE_7__ {TYPE_2__** pp_history; } ;
struct TYPE_11__ {TYPE_1__ context; TYPE_3__ ivtc; } ;
typedef  TYPE_5__ filter_sys_t ;

/* Variables and functions */
 size_t CADENCE_POS_BFF_ABC ; 
 size_t CADENCE_POS_BFF_BCD ; 
 size_t CADENCE_POS_BFF_CDE ; 
 size_t CADENCE_POS_BFF_EAB ; 
 scalar_t__ CADENCE_POS_INVALID ; 
 size_t CADENCE_POS_PROGRESSIVE ; 
 size_t CADENCE_POS_TFF_ABC ; 
 size_t CADENCE_POS_TFF_BCD ; 
 size_t CADENCE_POS_TFF_CDE ; 
 size_t CADENCE_POS_TFF_EAB ; 
 size_t IVTC_LATEST ; 
 int NUM_CADENCE_POS ; 
 int VEKTOR_CADENCE_POS_ALL ; 
 int VEKTOR_CADENCE_POS_BFF ; 
 int VEKTOR_CADENCE_POS_BFF_HIGH ; 
 int VEKTOR_CADENCE_POS_BFF_LOW ; 
 int VEKTOR_CADENCE_POS_TFF ; 
 int VEKTOR_CADENCE_POS_TFF_HIGH ; 
 int VEKTOR_CADENCE_POS_TFF_LOW ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int* pi_detected_pos_to_bitmask ; 

__attribute__((used)) static void IVTCCadenceDetectAlgoVektor( filter_t *p_filter )
{
    assert( p_filter != NULL );

    filter_sys_t *p_sys = p_filter->p_sys;
    ivtc_sys_t *p_ivtc  = &p_sys->ivtc;

    picture_t *p_next = p_sys->context.pp_history[2];

    assert( p_next != NULL );

    /* This algorithm is based on detecting hard-repeated fields (by motion
       detection), and conservatively estimating what the seen repeats could
       mean for the cadence position.

       "Conservative" means that we do not rule out possibilities if repeats
       are *not* seen, but only *add* possibilities based on what repeats
       *are* seen. This is important. Otherwise full-frame repeats in the
       original film (8fps or 12fps animation is very common in anime),
       causing spurious field repeats, would mess up the detection.
       With this strategy, spurious repeats will only slow down the lock-on,
       and will not break an existing lock-on once acquired.

       Several possibilities are kept open until the sequence gives enough
       information to make a unique detection. When the sequence becomes
       inconsistent (e.g. bad cut), the detector resets itself.

       The main ideas taken from the TVTime/Xine algorithm are:
        1) Conservatively using information from detected field repeats,
        2) Cadence counting the earlier detection results and combining with
           the new detection result, and
        3) The observation that video TFF/BFF uniquely determines TFD.

       The main differences are
        1) Different motion detection (see EstimateNumBlocksWithMotion()).
           Vektor's original estimates the average top/bottom field diff
           over the last 3 frames, while ours uses a block-based approach
           for diffing and just compares the field diffs between "curr" and
           "next" against each other (see IVTCLowLevelDetect()).
           Both approaches are adaptive, but in a different way.
        2) The specific detection logic used is a bit different (see both
           codes for details; the original is in xine-lib, function
           determine_pulldown_offset_short_history_new() in pulldown.c;
           ours is obviously given below). I think the one given here
           is a bit simpler.

       Note that we don't have to worry about getting a detection in all cases.
       It's enough if we work reliably, say, 99% of the time, and the other 1%
       of the time just admit that we don't know the cadence position.
       (This mostly happens after a bad cut, when the new scene has
       "difficult" motion characteristics, such as repeated film frames.)
       Our frame composer is built to handle also cases where we have no
       reliable detection of the cadence position; see IVTCOutputOrDropFrame().
       More important is to never lock on incorrectly, as this would both
       generate interlacing artifacts where none existed, and cause motion
       to stutter (because duplicate frames would be shown and unique ones
       dropped).
    */

    /* Progressive requires no repeats, so it is always a possibility.
       Filtering will drop it out if we know that the current position
       cannot be "dea".
    */
    int detected = 0;
    detected |= pi_detected_pos_to_bitmask[ CADENCE_POS_PROGRESSIVE ];

    /* Add in other possibilities depending on field repeats seen during the
       last three input frames (i.e. two transitions between input frames).
       See the "Dups." column in the cadence tables.
    */
    bool b_top_rep     = p_ivtc->pi_top_rep[IVTC_LATEST];
    bool b_bot_rep     = p_ivtc->pi_bot_rep[IVTC_LATEST];
    bool b_old_top_rep = p_ivtc->pi_top_rep[IVTC_LATEST-1];
    bool b_old_bot_rep = p_ivtc->pi_bot_rep[IVTC_LATEST-1];
    if( b_top_rep )
    {
        detected |= pi_detected_pos_to_bitmask[ CADENCE_POS_TFF_EAB ];
        detected |= pi_detected_pos_to_bitmask[ CADENCE_POS_BFF_BCD ];
    }
    if( b_old_top_rep )
    {
        detected |= pi_detected_pos_to_bitmask[ CADENCE_POS_TFF_ABC ];
        detected |= pi_detected_pos_to_bitmask[ CADENCE_POS_BFF_CDE ];
    }
    if( b_bot_rep )
    {
        detected |= pi_detected_pos_to_bitmask[ CADENCE_POS_TFF_BCD ];
        detected |= pi_detected_pos_to_bitmask[ CADENCE_POS_BFF_EAB ];
    }
    if( b_old_bot_rep )
    {
        detected |= pi_detected_pos_to_bitmask[ CADENCE_POS_TFF_CDE ];
        detected |= pi_detected_pos_to_bitmask[ CADENCE_POS_BFF_ABC ];
    }

    /* A TFF stream may only have TFF telecine, and similarly for BFF.
       Discard the possibility we know to be incorrect for this stream.
       (The stream may flipflop between the possibilities if it contains
        soft-telecined sequences or lone field repeats, so we must keep
        detecting this for each incoming frame.)
    */
    bool b_tff = p_next->b_top_field_first;
    if( b_tff )
        detected &= VEKTOR_CADENCE_POS_TFF;
    else
        detected &= VEKTOR_CADENCE_POS_BFF;

    /* Predict possible next positions based on our last detection.
       Begin with a shift and carry. */
    int predicted = p_ivtc->pi_v_raw[IVTC_LATEST-1];
    bool b_wrap_tff = false;
    bool b_wrap_bff = false;
    if( predicted & VEKTOR_CADENCE_POS_TFF_HIGH )
        b_wrap_tff = true;
    if( predicted & VEKTOR_CADENCE_POS_BFF_HIGH )
        b_wrap_bff = true;
    /* bump to next position and keep only valid bits */
    predicted = (predicted << 1) & VEKTOR_CADENCE_POS_ALL;
    /* carry */
    if( b_wrap_tff )
        predicted |= VEKTOR_CADENCE_POS_TFF_LOW;
    if( b_wrap_bff )
        predicted |= VEKTOR_CADENCE_POS_BFF_LOW;

    /* Filter: narrow down possibilities based on previous detection,
       if consistent. If not consistent, reset the detector.
       Reset works better than just using the latest raw detection.
    */
    if( (detected & predicted) != 0 )
        detected = detected & predicted;
    else
        detected = VEKTOR_CADENCE_POS_ALL;

    /* We're done. Save result to our internal storage so we can use it
       for prediction at the next frame.

       Note that the outgoing frame check in IVTCOutputOrDropFrame()
       has a veto right, resetting our state if it determines that
       the cadence has become broken.
    */
    p_ivtc->pi_v_raw[IVTC_LATEST] = detected;

    /* See if the position has been detected uniquely.
       If so, we have acquired a lock-on. */
    ivtc_cadence_pos exact = CADENCE_POS_INVALID;
    if( detected != 0 )
    {
        for( int i = 0; i < NUM_CADENCE_POS; i++ )
        {
            /* Note that we must use "&" instead of just equality to catch
               the progressive case, and also not to trigger on an incomplete
               detection. */
            if( detected == (detected & pi_detected_pos_to_bitmask[i]) )
            {
                exact = i;
                break;
            }
        }
    }

    /* If the result was unique, now "exact" contains the detected
       cadence position (and otherwise CADENCE_POS_INVALID).

       In practice, if the result from this algorithm is unique,
       it is always reliable.
    */
    p_ivtc->pi_v_cadence_pos[IVTC_LATEST] =  exact;
    p_ivtc->pb_v_reliable[IVTC_LATEST]    = (exact != CADENCE_POS_INVALID);
}