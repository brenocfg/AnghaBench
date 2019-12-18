#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int /*<<< orphan*/  p_segments; int /*<<< orphan*/  inner_align; } ;
struct TYPE_24__ {TYPE_3__ region; TYPE_2__* p_default_style; } ;
typedef  TYPE_4__ subtext_updater_sys_t ;
struct TYPE_21__ {TYPE_4__* p_sys; } ;
struct TYPE_25__ {int b_ephemer; int b_absolute; scalar_t__ i_stop; scalar_t__ i_start; TYPE_1__ updater; } ;
typedef  TYPE_5__ subpicture_t ;
struct TYPE_26__ {int /*<<< orphan*/  psz_alert_text; scalar_t__ alert_message_time_remaining; } ;
typedef  TYPE_6__ scte18_cea_t ;
struct TYPE_27__ {TYPE_8__* p_sys; } ;
typedef  TYPE_7__ decoder_t ;
struct TYPE_28__ {int /*<<< orphan*/  p_handle; } ;
typedef  TYPE_8__ decoder_sys_t ;
struct TYPE_29__ {int i_flags; scalar_t__ i_pts; } ;
typedef  TYPE_9__ block_t ;
struct TYPE_22__ {int i_style_flags; int i_features; int i_background_color; int i_font_color; int /*<<< orphan*/  i_background_alpha; } ;

/* Variables and functions */
 int BLOCK_FLAG_CORRUPTED ; 
 int /*<<< orphan*/  STYLE_ALPHA_OPAQUE ; 
 int STYLE_BACKGROUND ; 
 int STYLE_BOLD ; 
 int STYLE_HAS_BACKGROUND_ALPHA ; 
 int STYLE_HAS_BACKGROUND_COLOR ; 
 int STYLE_HAS_FLAGS ; 
 int STYLE_HAS_FONT_COLOR ; 
 int /*<<< orphan*/  SUBPICTURE_ALIGN_TOP ; 
 int VLCDEC_SUCCESS ; 
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  block_Release (TYPE_9__*) ; 
 TYPE_5__* decoder_NewSubpictureText (TYPE_7__*) ; 
 int /*<<< orphan*/  decoder_QueueSub (TYPE_7__*,TYPE_5__*) ; 
 int /*<<< orphan*/  msg_Info (TYPE_7__*,char*,int /*<<< orphan*/ ) ; 
 TYPE_6__* scte18_cea_Decode (int /*<<< orphan*/ ,TYPE_9__*) ; 
 int /*<<< orphan*/  scte18_cea_Free (TYPE_6__*) ; 
 int /*<<< orphan*/  text_segment_New (int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_tick_from_sec (scalar_t__) ; 

__attribute__((used)) static int Decode( decoder_t *p_dec, block_t *p_block )
{
    if ( p_block == NULL ) /* No Drain */
        return VLCDEC_SUCCESS;
    subpicture_t *p_spu = NULL;

    if (p_block->i_flags & (BLOCK_FLAG_CORRUPTED))
        goto exit;

    decoder_sys_t *p_sys = p_dec->p_sys;

    scte18_cea_t *p_cea = scte18_cea_Decode( p_sys->p_handle, p_block );
    if( p_cea )
    {
        p_spu = decoder_NewSubpictureText( p_dec );
        if( p_spu )
        {
            subtext_updater_sys_t *p_spu_sys = p_spu->updater.p_sys;

            p_spu->i_start = p_block->i_pts;
            if( p_cea->alert_message_time_remaining )
                p_spu->i_stop = p_spu->i_start + vlc_tick_from_sec( p_cea->alert_message_time_remaining );
            else
                p_spu->i_stop = VLC_TICK_INVALID;

            p_spu->b_ephemer  = true;
            p_spu->b_absolute = false;

            p_spu_sys->region.inner_align = SUBPICTURE_ALIGN_TOP;
            p_spu_sys->p_default_style->i_style_flags = STYLE_BOLD | STYLE_BACKGROUND;
            p_spu_sys->p_default_style->i_features |= STYLE_HAS_FLAGS;
            p_spu_sys->p_default_style->i_background_color = 0x000000;
            p_spu_sys->p_default_style->i_background_alpha = STYLE_ALPHA_OPAQUE;
            p_spu_sys->p_default_style->i_features |= STYLE_HAS_BACKGROUND_COLOR | STYLE_HAS_BACKGROUND_ALPHA;
            p_spu_sys->p_default_style->i_font_color = 0xFF0000;
            p_spu_sys->p_default_style->i_features |= STYLE_HAS_FONT_COLOR;

            p_spu_sys->region.p_segments = text_segment_New( p_cea->psz_alert_text );
            decoder_QueueSub( p_dec, p_spu );
        }
        msg_Info( p_dec, "Received %s", p_cea->psz_alert_text );
        scte18_cea_Free( p_cea );
    }

exit:
    block_Release( p_block );
    return VLCDEC_SUCCESS;
}