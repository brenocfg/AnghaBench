#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_16__ {scalar_t__ date; int i_nb_fields; scalar_t__ b_top_field_first; } ;
typedef  TYPE_2__ picture_t ;
struct TYPE_17__ {scalar_t__ i_mode; int b_sequence_valid; size_t i_cadence_pos; size_t i_tfd; int* pi_scores; int* pi_final_scores; int /*<<< orphan*/ * pi_v_raw; } ;
typedef  TYPE_3__ ivtc_sys_t ;
struct TYPE_18__ {TYPE_5__* p_sys; } ;
typedef  TYPE_4__ filter_t ;
struct TYPE_15__ {TYPE_2__** pp_history; } ;
struct TYPE_19__ {TYPE_1__ context; TYPE_3__ ivtc; } ;
typedef  TYPE_5__ filter_sys_t ;

/* Variables and functions */
 size_t CADENCE_POS_INVALID ; 
 int /*<<< orphan*/  CC_ALTLINE ; 
 int /*<<< orphan*/  ComposeFrame (TYPE_4__*,TYPE_2__*,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 size_t FIELD_PAIR_TCBC ; 
 size_t FIELD_PAIR_TCBN ; 
 size_t FIELD_PAIR_TNBC ; 
 size_t FIELD_PAIR_TNBN ; 
 int IVTC_DETECTION_HISTORY_SIZE ; 
 size_t IVTC_LATEST ; 
 scalar_t__ IVTC_MODE_TELECINED_NTSC_HARD ; 
 scalar_t__ IVTC_MODE_TELECINED_NTSC_SOFT ; 
 int IVTC_OP_COMPOSE_TCBN ; 
 int IVTC_OP_COMPOSE_TNBC ; 
 int IVTC_OP_COPY_C ; 
 int IVTC_OP_COPY_N ; 
 int IVTC_OP_DROP_FRAME ; 
 size_t TFD_INVALID ; 
 int /*<<< orphan*/  VEKTOR_CADENCE_POS_ALL ; 
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_4__*,char*,int,int) ; 
 int** pi_reconstruction_ops ; 
 int* pi_timestamp_deltas ; 
 int /*<<< orphan*/  picture_Copy (TYPE_2__*,TYPE_2__*) ; 

__attribute__((used)) static bool IVTCOutputOrDropFrame( filter_t *p_filter, picture_t *p_dst )
{
    assert( p_filter != NULL );
    assert( p_dst != NULL );

    filter_sys_t *p_sys = p_filter->p_sys;
    ivtc_sys_t *p_ivtc  = &p_sys->ivtc;
    vlc_tick_t t_final = VLC_TICK_INVALID; /* for custom timestamp mangling */

    picture_t *p_curr = p_sys->context.pp_history[1];
    picture_t *p_next = p_sys->context.pp_history[2];

    assert( p_next != NULL );
    assert( p_curr != NULL );

    /* Perform IVTC if we're in film mode (either hard or soft telecine).

       Note that we don't necessarily have a lock-on, even if we are in
       IVTC_MODE_TELECINED_NTSC_HARD. We *may* be locked on, or alternatively,
       we have seen a valid cadence some time in the past, but lock-on has
       since been lost, and we have not seen a progressive signal after that.
       The latter case usually results from bad cuts, which interrupt
       the cadence.

       Lock-on state is given by p_ivtc->b_sequence_valid.
    */
    int i_result_score = -1;
    int op;
    if( p_ivtc->i_mode == IVTC_MODE_TELECINED_NTSC_HARD )
    {
        /* Decide what to do. The operation table is only enabled
           if the cadence seems reliable. Otherwise we use a backup strategy.
        */
        if( p_ivtc->b_sequence_valid )
        {
            assert( p_ivtc->i_cadence_pos != CADENCE_POS_INVALID );
            assert( p_ivtc->i_tfd != TFD_INVALID );

            /* Pick correct operation from the operation table. */
            op = pi_reconstruction_ops[p_ivtc->i_tfd][p_ivtc->i_cadence_pos];

            if( op == IVTC_OP_DROP_FRAME )
            {
                /* Bump cadence counter into the next expected position */
                p_ivtc->i_cadence_pos = (p_ivtc->i_cadence_pos + 1) % 5;

                /* Drop frame. We're done. */
                return false;
            }
            else
            {
                if( op == IVTC_OP_COPY_N )
                    i_result_score = p_ivtc->pi_scores[FIELD_PAIR_TNBN];
                else if( op == IVTC_OP_COPY_C )
                    i_result_score = p_ivtc->pi_scores[FIELD_PAIR_TCBC];
                else if( op == IVTC_OP_COMPOSE_TNBC )
                    i_result_score = p_ivtc->pi_scores[FIELD_PAIR_TNBC];
                else if( op == IVTC_OP_COMPOSE_TCBN )
                    i_result_score = p_ivtc->pi_scores[FIELD_PAIR_TCBN];

                /* Sanity check the result */

                /* Compute running mean of outgoing interlace score.
                   See below for history mechanism. */
                int i_avg = 0;
                for( int i = 0; i < IVTC_DETECTION_HISTORY_SIZE; i++)
                    i_avg += p_ivtc->pi_final_scores[i];
                i_avg /= IVTC_DETECTION_HISTORY_SIZE;

                /* Check if the score suddenly became "clearly larger".
                   Also, filter out spurious peaks at the low end. */
                if( i_result_score > 1000  &&  i_result_score > 2*i_avg )
                {
                    /* Sequence wasn't reliable after all; we'll use
                       the Transcode strategy for this frame. */
                    p_ivtc->b_sequence_valid = false;
                    msg_Dbg( p_filter, "Rejected cadence-based frame "\
                                       "construction: interlace score %d "\
                                       "(running average %d)",
                                       i_result_score, i_avg );

                    /* We also reset the detector used in the "vektor"
                       algorithm, as it depends on having a reliable previous
                       position. In practice, we continue using the Transcode
                       strategy until the cadence becomes locked on again.
                       (At that point, b_sequence_valid will become true again,
                       and we continue with this strategy.)
                    */
                    p_ivtc->pi_v_raw[IVTC_LATEST] = VEKTOR_CADENCE_POS_ALL;
                }
            }
        }

        /* Frame not dropped, and the cadence counter seems unreliable.

            Note that this is not an "else" to the previous case. This may
            begin with a valid sequence, and then the above logic decides
            that it wasn't valid after all.
        */
        if( !p_ivtc->b_sequence_valid )
        {
            /* In this case, we must proceed with no cadence information.
                We use a Transcode-like strategy.

                We check which field paired with TN or BN (accounting for
                the field dominance) gives the smallest interlace score,
                and declare that combination the resulting progressive frame.

                This strategy gives good results on average, but often fails
                in talking scenes in anime. Those can be handled more reliably
                with a locked-on cadence produced by the "vektor" algorithm.
            */

            int tnbn = p_ivtc->pi_scores[FIELD_PAIR_TNBN]; /* TFF and BFF */
            int tnbc = p_ivtc->pi_scores[FIELD_PAIR_TNBC]; /* TFF only */
            int tcbn = p_ivtc->pi_scores[FIELD_PAIR_TCBN]; /* BFF only */

            if( p_next->b_top_field_first )
            {
                if( tnbn <= tnbc )
                {
                    op = IVTC_OP_COPY_N;
                    i_result_score = tnbn;
                }
                else
                {
                    op = IVTC_OP_COMPOSE_TNBC;
                    i_result_score = tnbc;
                }
            }
            else
            {
                if( tnbn <= tcbn )
                {
                    op = IVTC_OP_COPY_N;
                    i_result_score = tnbn;
                }
                else
                {
                    op = IVTC_OP_COMPOSE_TCBN;
                    i_result_score = tcbn;
                }
            }
        }

        /* Mangle timestamps when locked on.

           "Current" is the frame that is being extracted now. Use its original
           timestamp as the base.

           Note that this way there will be no extra delay compared to the
           raw stream, even though we look one frame into the future.
        */
        if( p_ivtc->b_sequence_valid )
        {
            /* Convert 29.97 -> 23.976 fps. We get to this point only if we
               didn't drop the frame, so we always get a valid delta.
            */
            int i_timestamp_delta = pi_timestamp_deltas[p_ivtc->i_cadence_pos];
            assert( i_timestamp_delta >= 0 );

            /* FIXME: use field length as measured by Deinterlace()? */
            t_final = p_curr->date
                    + (p_next->date - p_curr->date)*i_timestamp_delta/4;
        }
        else /* Do not mangle timestamps (or drop frames, either) if cadence
                is not locked on. This causes one of five output frames - if
                all are reconstructed correctly - to be a duplicate, but in
                practice at least with anime (which is the kind of material
                that tends to have this problem) this is less noticeable than
                a sudden jump in the cadence. Especially, a consistently wrong
                lock-on will cause a very visible stutter, which we wish
                to avoid. */
        {
            t_final = p_curr->date;
        }

        /* Bump cadence counter into the next expected position. */
        p_ivtc->i_cadence_pos = (p_ivtc->i_cadence_pos + 1) % 5;
    }
    else if( p_ivtc->i_mode == IVTC_MODE_TELECINED_NTSC_SOFT )
    {
        /* Soft telecine. We have the progressive frames already;
           even out PTS diffs only. */

        /* Pass through the "current" frame. We must choose the frame "current"
           in order to be able to detect soft telecine before we have to output
           the frame. See IVTCSoftTelecineDetect(). Also, this allows
           us to peek at the next timestamp to calculate the duration of
           "current".
        */
        op = IVTC_OP_COPY_C;
        i_result_score = p_ivtc->pi_scores[FIELD_PAIR_TCBC];

        /* Timestamp mangling for soft telecine: bump "threes" forward by
           0.5 field durations. This is more forgiving for the renderer
           than bumping the "twos" back (which would require to render
           them sooner),
        */
        if( p_curr->i_nb_fields == 3 )
        {
            /* Approximate field duration from the PTS difference. */
            /* FIXME: use field length as measured by Deinterlace()? */
            vlc_tick_t i_half_field_dur = ( (p_next->date - p_curr->date)/3 ) / 2;
            t_final = p_curr->date + i_half_field_dur;
        }
        else /* Otherwise, use original PTS of the outgoing frame. */
        {
            t_final = p_curr->date;
        }
    }
    else /* Not film mode, timestamp mangling bypassed. */
    {
        op = IVTC_OP_COPY_N;
        i_result_score = p_ivtc->pi_scores[FIELD_PAIR_TNBN];

        /* Preserve original PTS (note that now, in principle,
                                  "next" is the outgoing frame) */
        t_final = p_next->date;
    }

    /* There is only one case where we should drop the frame,
       and it was already handled above. */
    assert( op != IVTC_OP_DROP_FRAME );

    /* Render into p_dst according to the final operation chosen. */
    if( op == IVTC_OP_COPY_N )
        picture_Copy( p_dst, p_next );
    else if( op == IVTC_OP_COPY_C )
        picture_Copy( p_dst, p_curr );
    else if( op == IVTC_OP_COMPOSE_TNBC )
        ComposeFrame( p_filter, p_dst, p_next, p_curr, CC_ALTLINE, false );
    else if( op == IVTC_OP_COMPOSE_TCBN )
        ComposeFrame( p_filter, p_dst, p_curr, p_next, CC_ALTLINE, false );

    /* Slide history of outgoing interlace scores. This must be done last,
       and only if the frame was not dropped, so we do it here.

       This is used during the reconstruction to get an idea of what is
       (in the temporally local sense) an acceptable interlace score
       for a correctly reconstructed frame. See above.
    */
    for( int i = 1; i < IVTC_DETECTION_HISTORY_SIZE; i++ )
        p_ivtc->pi_final_scores[i-1] = p_ivtc->pi_final_scores[i];
    p_ivtc->pi_final_scores[IVTC_LATEST] = i_result_score;

    /* Note that picture_Copy() copies the PTS, too. Apply timestamp mangling
       now, if any was needed.
    */
    if( t_final != VLC_TICK_INVALID )
        p_dst->date = t_final;

    return true;
}