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
typedef  int uint64_t ;
struct TYPE_8__ {int /*<<< orphan*/  b_top_field_first; } ;
typedef  TYPE_2__ picture_t ;
struct TYPE_9__ {int* pi_scores; int* pi_s_cadence_pos; int* pi_cadence_pos_history; int* pi_motion; int* pb_s_reliable; } ;
typedef  TYPE_3__ ivtc_sys_t ;
typedef  int int64_t ;
struct TYPE_10__ {TYPE_5__* p_sys; } ;
typedef  TYPE_4__ filter_t ;
struct TYPE_7__ {TYPE_2__** pp_history; } ;
struct TYPE_11__ {TYPE_1__ context; TYPE_3__ ivtc; } ;
typedef  TYPE_5__ filter_sys_t ;

/* Variables and functions */
 int CADENCE_POS_BFF_END ; 
 int CADENCE_POS_BFF_FIRST ; 
 int CADENCE_POS_INVALID ; 
 size_t CADENCE_POS_PROGRESSIVE ; 
 int CADENCE_POS_TFF_END ; 
 int CADENCE_POS_TFF_FIRST ; 
 size_t IVTC_LATEST ; 
 int NUM_CADENCE_POS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 size_t** pi_best_field_pairs ; 
 int* pi_detected_pos_to_cadence_pos ; 

__attribute__((used)) static void IVTCCadenceDetectAlgoScores( filter_t *p_filter )
{
    assert( p_filter != NULL );

    filter_sys_t *p_sys = p_filter->p_sys;
    ivtc_sys_t *p_ivtc  = &p_sys->ivtc;
    picture_t *p_next = p_sys->context.pp_history[2];

    assert( p_next != NULL );

    /* Detect likely cadence position according to the tables,
       using the tabulated combinations of all 7 available interlace scores.
    */
    int pi_ivtc_scores[NUM_CADENCE_POS];
    for( int i = 0; i < NUM_CADENCE_POS; i++ )
        pi_ivtc_scores[i] = p_ivtc->pi_scores[ pi_best_field_pairs[i][0] ]
                          + p_ivtc->pi_scores[ pi_best_field_pairs[i][1] ]
                          + p_ivtc->pi_scores[ pi_best_field_pairs[i][2] ];
    /* Find minimum */
    int j = CADENCE_POS_PROGRESSIVE; /* valid regardless of TFD */
    int minscore = pi_ivtc_scores[j];
    /* A TFF (respectively BFF) stream may only have TFF (respectively BFF)
       telecine. Don't bother looking at the wrong table. */
    int imin = CADENCE_POS_TFF_FIRST; /* first TFF-only entry */
    int iend = CADENCE_POS_TFF_END;   /* one past last TFF-only entry */
    if( !p_next->b_top_field_first )
    {
        imin = CADENCE_POS_BFF_FIRST; /* first BFF-only entry */
        iend = CADENCE_POS_BFF_END;   /* one past last BFF-only entry */
    }
    for( int i = imin; i < iend; i++ )
    {
        if( pi_ivtc_scores[i] < minscore )
        {
            minscore = pi_ivtc_scores[i];
            j = i;
        }
    }

    /* Now "j" contains the most likely position according to the tables,
       accounting also for video TFF/BFF. */
    p_ivtc->pi_s_cadence_pos[IVTC_LATEST] = j;

    /* Estimate reliability of detector result.

       We do this by checking if the winner is an outlier at least
       to some extent. For anyone better versed in statistics,
       feel free to improve this.
    */

    /* Compute sample mean with the winner included and without.

       Sample mean is defined as mu = sum( x_i, i ) / N ,
       where N is the number of samples.
    */
    int mean = pi_ivtc_scores[CADENCE_POS_PROGRESSIVE];
    int mean_except_min = 0;
    if( j != CADENCE_POS_PROGRESSIVE )
        mean_except_min = pi_ivtc_scores[CADENCE_POS_PROGRESSIVE];
    for( int i = imin; i < iend; i++ )
    {
        mean += pi_ivtc_scores[i];
        if( i != j )
            mean_except_min += pi_ivtc_scores[i];
    }
    /* iend points one past end, but progressive counts as the +1. */
    mean /= (iend - imin + 1);
    mean_except_min /= (iend - imin);

    /* Check how much excluding the winner changes the mean. */
    double mean_ratio = (double)mean_except_min / (double)mean;

    /* Let's pretend that the detected position is a stochastic variable.
       Compute sample variance with the winner included and without.

       var = sum( (x_i - mu)^2, i ) / N ,

       where mu is the sample mean.

       Note that we really need int64_t; the numbers are pretty large.
    */
    int64_t diff = (int64_t)(pi_ivtc_scores[CADENCE_POS_PROGRESSIVE] - mean);
    int64_t var = diff*diff;
    int64_t var_except_min = 0;
    if( j != CADENCE_POS_PROGRESSIVE )
    {
        int64_t diff_exm = (int64_t)(pi_ivtc_scores[CADENCE_POS_PROGRESSIVE]
                                      - mean_except_min);
        var_except_min = diff_exm*diff_exm;
    }
    for( int i = imin; i < iend; i++ )
    {
        diff = (int64_t)(pi_ivtc_scores[i] - mean);
        var += (diff*diff);
        if( i != j )
        {
            int64_t diff_exm = (int64_t)(pi_ivtc_scores[i] - mean_except_min);
            var_except_min += (diff_exm*diff_exm);
        }
    }
    /* iend points one past end, but progressive counts as the +1. */
    var /= (uint64_t)(iend - imin + 1);
    var_except_min /= (uint64_t)(iend - imin);

    /* Extract cadence counter part of detected positions for the
       last two frames.

       Note that for the previous frame, we use the final detected cadence
       position, which was not necessarily produced by this algorithm.
       It is the result that was judged the most reliable.
    */
    int j_curr = p_ivtc->pi_cadence_pos_history[IVTC_LATEST-1];
    int pos_next = pi_detected_pos_to_cadence_pos[j];

    /* Be optimistic when unsure. We bias the detection toward accepting
       the next "correct" position, even if the variance check comes up bad.
    */
    bool b_expected = false;
    if( j_curr != CADENCE_POS_INVALID )
    {
        int pos_curr = pi_detected_pos_to_cadence_pos[j_curr];
        b_expected = (pos_next == (pos_curr + 1) % 5);
    }

    /* Use motion detect result as a final sanity check.
       If no motion, the result from this algorithm cannot be reliable.
    */
    int i_blocks_with_motion = p_ivtc->pi_motion[IVTC_LATEST];

    /* The numbers given here are empirical constants that have been tuned
       through trial and error. The test material used was NTSC anime DVDs.

        Easy-to-detect parts seem to give variance boosts of 40-70%, but
        hard-to-detect parts sometimes only 18%. Anything with a smaller boost
        in variance doesn't seem reliable for catching a new lock-on,

        Additionally, it seems that if the mean changes by less than 0.5%,
        the result is not reliable.

        Note that the numbers given are only valid for the pi_best_field_pairs
        detector strategy.

        For motion detection, the detector seems good enough so that
        we can threshold at zero.
    */
    bool b_result_reliable =
      ( i_blocks_with_motion > 0      &&
        mean_ratio           > 1.005  &&
        ( b_expected || ( (double)var > 1.17*(double)var_except_min ) )
      );
    p_ivtc->pb_s_reliable[IVTC_LATEST] = b_result_reliable;
}