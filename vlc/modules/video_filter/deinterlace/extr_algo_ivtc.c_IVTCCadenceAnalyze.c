#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int i_nb_fields; } ;
typedef  TYPE_2__ picture_t ;
struct TYPE_10__ {int* pi_cadence_pos_history; int* pi_motion; int b_sequence_valid; int* pb_all_progressives; scalar_t__ i_mode; int i_cadence_pos; int i_tfd; } ;
typedef  TYPE_3__ ivtc_sys_t ;
struct TYPE_11__ {TYPE_5__* p_sys; } ;
typedef  TYPE_4__ filter_t ;
struct TYPE_8__ {TYPE_2__** pp_history; } ;
struct TYPE_12__ {TYPE_1__ context; TYPE_3__ ivtc; } ;
typedef  TYPE_5__ filter_sys_t ;

/* Variables and functions */
 int CADENCE_POS_INVALID ; 
 int IVTC_DETECTION_HISTORY_SIZE ; 
 size_t IVTC_LATEST ; 
 scalar_t__ IVTC_MODE_DETECTING ; 
 scalar_t__ IVTC_MODE_TELECINED_NTSC_HARD ; 
 int TFD_BFF ; 
 int TFD_INVALID ; 
 int TFD_TFF ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_4__*,char*) ; 
 int* pi_detected_pos_to_cadence_pos ; 
 int* pi_detected_pos_to_tfd ; 

__attribute__((used)) static void IVTCCadenceAnalyze( filter_t *p_filter )
{
    assert( p_filter != NULL );

    filter_sys_t *p_sys = p_filter->p_sys;
    ivtc_sys_t *p_ivtc  = &p_sys->ivtc;
    picture_t *p_prev = p_sys->context.pp_history[0];
    picture_t *p_curr = p_sys->context.pp_history[1];
    picture_t *p_next = p_sys->context.pp_history[2];

    assert( p_next != NULL );
    assert( p_curr != NULL );
    assert( p_prev != NULL );

    /* Determine which frames in the buffer qualify for analysis.

       Note that hard telecine always has nb_fields = 2 and
       video TFF = constant (i.e. the stream flags look no different from
       a true interlaced or true progressive stream). Basically, no one ever
       sets the progressive frame flag for the input frames d, e, and a -
       in practice they're all flagged as interlaced.

       A frame may qualify for hard TC analysis if it has no soft field repeat
       (i.e. it cannot be part of a soft telecine). The condition
       nb_fields == 2 must always match.

       Additionally, curr and next must have had motion with respect to the
       previous frame, to ensure that the different field combinations have
       produced unique pictures.

       Alternatively, if there was no motion, but the cadence position was
       reliably detected and it was the expected one, we qualify the frame
       for analysis (mainly, for TFD voting).

       We only proceed with the cadence analysis if all three frames
       in the buffer qualify.
    */

    /* Note that these are the final detected positions
       produced by IVTCCadenceDetectFinalize(). */
    int j_next = p_ivtc->pi_cadence_pos_history[IVTC_LATEST];
    int j_curr = p_ivtc->pi_cadence_pos_history[IVTC_LATEST-1];
    int j_prev = p_ivtc->pi_cadence_pos_history[IVTC_LATEST-2];

    bool b_expected = false;
    if( j_next != CADENCE_POS_INVALID  &&  j_curr != CADENCE_POS_INVALID )
    {
        int pos_next = pi_detected_pos_to_cadence_pos[j_next];
        int pos_curr = pi_detected_pos_to_cadence_pos[j_curr];
        b_expected = (pos_next == (pos_curr + 1) % 5);
    }
    bool b_old_expected  = false;
    if( j_curr != CADENCE_POS_INVALID  &&  j_prev != CADENCE_POS_INVALID )
    {
        int pos_curr = pi_detected_pos_to_cadence_pos[j_curr];
        int pos_prev = pi_detected_pos_to_cadence_pos[j_prev];
        b_old_expected = (pos_curr == (pos_prev + 1) % 5);
    }

    int i_motion     = p_ivtc->pi_motion[IVTC_LATEST];
    int i_old_motion = p_ivtc->pi_motion[IVTC_LATEST-1];

    bool b_prev_valid  = (p_prev->i_nb_fields == 2);
    bool b_curr_valid  = (p_curr->i_nb_fields == 2)  &&
                         (i_old_motion > 0  ||  b_old_expected);
    bool b_next_valid  = (p_next->i_nb_fields == 2)  &&
                         (i_motion > 0      ||  b_expected);
    bool b_no_invalids = (b_prev_valid && b_curr_valid && b_next_valid);

    /* Final sanity check: see that the detection history has been
       completely filled,  i.e. the latest three positions of the stencil
       have given a result from the cadence detector.
    */
    if( b_no_invalids )
    {
        for( int i = 0; i < IVTC_DETECTION_HISTORY_SIZE; ++i )
        {
            const int i_detected_pos = p_ivtc->pi_cadence_pos_history[i];
            if( i_detected_pos == CADENCE_POS_INVALID )
            {
                b_no_invalids = false;
                break;
            }
        }
    }

    /* If still ok, do the analysis. */
    p_ivtc->b_sequence_valid = false; /* needed in frame reconstruction */
    if( b_no_invalids )
    {
        /* Convert the history elements to cadence position and TFD. */
        int pi_tfd[IVTC_DETECTION_HISTORY_SIZE];
        int pi_pos[IVTC_DETECTION_HISTORY_SIZE];
        for( int i = 0; i < IVTC_DETECTION_HISTORY_SIZE; ++i )
        {
            const int i_detected_pos = p_ivtc->pi_cadence_pos_history[i];
            pi_pos[i] = pi_detected_pos_to_cadence_pos[i_detected_pos];
            pi_tfd[i] = pi_detected_pos_to_tfd[i_detected_pos];
        }

        /* See if the sequence is valid. The cadence positions must be
           successive mod 5. We can't say anything about TFF/BFF yet,
           because the progressive-looking position "dea" may be there.
           If the sequence otherwise looks valid, we handle that last
           by voting.

           We also test for a progressive signal here, so that we know
           when to exit IVTC_MODE_TELECINED_NTSC_HARD.
        */
        p_ivtc->b_sequence_valid = true;
        bool b_all_progressive = (pi_pos[0] == 3);
        int j = pi_pos[0];
        for( int i = 1; i < IVTC_DETECTION_HISTORY_SIZE; ++i )
        {
            if( pi_pos[i] != (++j % 5) )
                p_ivtc->b_sequence_valid = false;
            if( pi_pos[i] != 3 )
                b_all_progressive = false;
        }
        p_ivtc->pb_all_progressives[IVTC_LATEST] = b_all_progressive;

        if( p_ivtc->b_sequence_valid )
        {
            /* Determine TFF/BFF. */
            int i_vote_invalid = 0;
            int i_vote_tff     = 0;
            int i_vote_bff     = 0;
            for( int i = 0; i < IVTC_DETECTION_HISTORY_SIZE; ++i )
            {
                if( pi_tfd[i] == TFD_INVALID )
                    i_vote_invalid++;
                else if( pi_tfd[i] == TFD_TFF )
                    i_vote_tff++;
                else if( pi_tfd[i] == TFD_BFF )
                    i_vote_bff++;
            }

            /* With three entries, two votes for any one item are enough
               to decide this conclusively. */
            int i_telecine_field_dominance = TFD_INVALID;
            if( i_vote_tff >= 2)
                i_telecine_field_dominance = TFD_TFF;
            else if( i_vote_bff >= 2)
                i_telecine_field_dominance = TFD_BFF;
            /* In all other cases, "invalid" won or no winner.
               This means no NTSC telecine detected. */

            /* Lock on to the cadence if it was valid and TFF/BFF was found.

               Also, aggressively update the cadence counter from the
               lock-on data whenever we can. In practice this has been found
               to be a reliable strategy (if the cadence detectors are
               good enough).
            */
            if( i_telecine_field_dominance == TFD_TFF )
            {
                if( p_ivtc->i_mode != IVTC_MODE_TELECINED_NTSC_HARD )
                    msg_Dbg( p_filter, "IVTC: 3:2 pulldown: NTSC TFF "\
                                       "hard telecine detected." );
                p_ivtc->i_mode        = IVTC_MODE_TELECINED_NTSC_HARD;
                p_ivtc->i_cadence_pos = pi_pos[IVTC_LATEST];
                p_ivtc->i_tfd         = TFD_TFF;
            }
            else if( i_telecine_field_dominance == TFD_BFF )
            {
                if( p_ivtc->i_mode != IVTC_MODE_TELECINED_NTSC_HARD )
                    msg_Dbg( p_filter, "IVTC: 3:2 pulldown: NTSC BFF "\
                                       "hard telecine detected." );
                p_ivtc->i_mode        = IVTC_MODE_TELECINED_NTSC_HARD;
                p_ivtc->i_cadence_pos = pi_pos[IVTC_LATEST];
                p_ivtc->i_tfd         = TFD_BFF;
            }
        }
        /* No telecine... maybe a progressive signal? */
        else if( b_all_progressive )
        {
            /* It seems that in practice, three "3"s in a row can still be
               a fluke rather often. Four or five usually are not.
               This fixes the Stellvia OP. */

            bool b_really_all_progressive = true;
            for( int i = 0; i < IVTC_DETECTION_HISTORY_SIZE ; i++ )
            {
                if( p_ivtc->pb_all_progressives[i] == false )
                {
                    b_really_all_progressive = false;
                    break;
                }
            }

            /* If we still think the signal is progressive... */
            if( b_really_all_progressive )
            {
                /* ...exit film mode immediately. This does not break
                   soft TC handling, because for soft TC at least one
                   of the frames will not qualify (due to i_nb_fields == 3),
                   and in that case this analysis will not run.
                */
                if( p_ivtc->i_mode == IVTC_MODE_TELECINED_NTSC_HARD )
                    msg_Dbg( p_filter, "IVTC: 3:2 pulldown: progressive "\
                                       "signal detected." );
                p_ivtc->i_mode        = IVTC_MODE_DETECTING;
                p_ivtc->i_cadence_pos = CADENCE_POS_INVALID;
                p_ivtc->i_tfd         = TFD_INVALID;
            }
        }
        /* Final missing "else": no valid NTSC telecine sequence detected.

           Either there is no telecine, or the detector - although it produced
           results - had trouble finding it. In this case we do nothing,
           as it's not a good idea to act on unreliable data.

           Note that if we are already in IVTC_MODE_TELECINED_NTSC_HARD, this
           case means that we have lost the lock-on, but are still (probably)
           in a hard-telecined stream. This will start the emergency mode
           for film frame reconstruction. See IVTCOutputOrDropFrame().
        */
    }
}