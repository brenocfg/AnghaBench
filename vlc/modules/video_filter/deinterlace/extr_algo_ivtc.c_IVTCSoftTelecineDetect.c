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
struct TYPE_9__ {int i_nb_fields; int /*<<< orphan*/  b_top_field_first; } ;
typedef  TYPE_2__ picture_t ;
struct TYPE_10__ {scalar_t__ i_mode; scalar_t__ i_old_mode; int i_tfd; scalar_t__ i_cadence_pos; } ;
typedef  TYPE_3__ ivtc_sys_t ;
struct TYPE_11__ {TYPE_5__* p_sys; } ;
typedef  TYPE_4__ filter_t ;
struct TYPE_8__ {TYPE_2__** pp_history; } ;
struct TYPE_12__ {TYPE_1__ context; TYPE_3__ ivtc; } ;
typedef  TYPE_5__ filter_sys_t ;

/* Variables and functions */
 scalar_t__ CADENCE_POS_INVALID ; 
 scalar_t__ IVTC_MODE_TELECINED_NTSC_SOFT ; 
 int TFD_INVALID ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_4__*,char*) ; 

__attribute__((used)) static void IVTCSoftTelecineDetect( filter_t *p_filter )
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

    /* Soft telecine can be detected from the flag pattern:
       nb_fields = 3,2,3,2,... and *video* TFF = true, false, false, true
       (TFF telecine) or false, true, true, false (BFF telecine).

       We don't particularly care which field goes first, because in soft TC
       we're working with progressive frames. And in any case, the video FDs
       of successive frames must match any field repeats in order for field
       renderers (such as traditional DVD player + CRT TV) to work correctly.
       Thus the video TFF/BFF flag provides no additional useful information
       for us on top of checking nb_fields.

       The only thing to *do* to soft telecine in an IVTC filter is to even
       out the outgoing PTS diffs to 2.5 fields each, so that we get
       a steady 24fps output. Thus, we can do this processing even if it turns
       out that we saw a lone field repeat (which are also sometimes used,
       such as in the Silent Mobius OP and in Sol Bianca). We can be aggressive
       and don't need to care about false positives - as long as we are equally
       aggressive about dropping out of soft telecine mode the moment a "2" is
       followed by another "2" and not a "3" as in soft TC.

       Finally, we conclude that the one-frame future buffer is enough for us
       to make soft TC decisions just in time for rendering the frame in the
       "current" position. The flag patterns given below constitute proof
       of this property.

       Soft telecine is relatively rare at least in anime, but it exists;
       e.g. Angel Links OP, Silent Mobius, and Stellvia of the Universe have
       sequences that are soft telecined. Stellvia, especially, alternates
       between soft and hard telecine all the time.
    */

    /* Valid stream flag patterns for soft telecine. There are three: */

    /* Entering soft telecine at frame curr, or running inside it already */
    bool b_soft_telecine_1 = (p_prev->i_nb_fields == 2) &&
                             (p_curr->i_nb_fields == 3) &&
                             (p_next->i_nb_fields == 2);
    /* Running inside soft telecine */
    bool b_soft_telecine_2 = (p_prev->i_nb_fields == 3) &&
                             (p_curr->i_nb_fields == 2) &&
                             (p_next->i_nb_fields == 3);
    /* Exiting soft telecine at frame curr (curr is the last frame
       that should be handled as soft TC) */
    bool b_soft_telecine_3 = (p_prev->i_nb_fields == 3) &&
                             (p_curr->i_nb_fields == 2) &&
                             (p_next->i_nb_fields == 2);

    /* Soft telecine is very clear-cut - the moment we see or do not see
       a valid flag pattern, we can change the filter mode.
    */
    if( b_soft_telecine_1 || b_soft_telecine_2 || b_soft_telecine_3 )
    {
        if( p_ivtc->i_mode != IVTC_MODE_TELECINED_NTSC_SOFT )
        {
            msg_Dbg( p_filter, "IVTC: 3:2 pulldown: NTSC soft telecine "\
                               "detected." );
            p_ivtc->i_old_mode = p_ivtc->i_mode;
        }

        /* Valid flag pattern seen, this frame is soft telecined */
        p_ivtc->i_mode = IVTC_MODE_TELECINED_NTSC_SOFT;

        /* Only used during IVTC'ing hard telecine. */
        p_ivtc->i_cadence_pos = CADENCE_POS_INVALID;
        p_ivtc->i_tfd         = TFD_INVALID;
    }
    /* Note: no flag pattern match now */
    else if( p_ivtc->i_mode == IVTC_MODE_TELECINED_NTSC_SOFT )
    {
        msg_Dbg( p_filter, "IVTC: 3:2 pulldown: NTSC soft telecine ended. "\
                           "Returning to previous mode." );

        /* No longer soft telecined, return filter to the mode it had earlier.
           This is needed to fix cases where we came in from hard telecine, and
           should go back, but can't catch a cadence in time before telecined
           frames slip through. Kickstarting back to hard IVTC, using the
           emergency frame composer until the cadence locks on again,
           fixes the problem. This happens a lot in Stellvia.
        */
        p_ivtc->i_mode = p_ivtc->i_old_mode;
        p_ivtc->i_cadence_pos = 0; /* Wild guess. The film frame reconstruction
                                      will start in emergency mode, and this
                                      will be filled in by the detector ASAP.*/
        /* I suppose video field dominance no longer flipflops. */
        p_ivtc->i_tfd = !p_next->b_top_field_first; /* tff  <=>  TFD == 0 */
    }
}