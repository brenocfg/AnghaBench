#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int i_cat; } ;
struct TYPE_5__ {TYPE_1__ fmt_out; } ;
struct decoder_owner {float output_rate; int /*<<< orphan*/  lock; int /*<<< orphan*/  i_spu_channel; int /*<<< orphan*/ * p_vout; int /*<<< orphan*/ * p_aout; TYPE_2__ dec; } ;
typedef  TYPE_2__ decoder_t ;

/* Variables and functions */
#define  AUDIO_ES 130 
#define  SPU_ES 129 
#define  VIDEO_ES 128 
 int /*<<< orphan*/  VOUT_SPU_CHANNEL_INVALID ; 
 int /*<<< orphan*/  aout_DecChangeRate (int /*<<< orphan*/ *,float) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*,float) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_ChangeRate (int /*<<< orphan*/ *,float) ; 
 int /*<<< orphan*/  vout_ChangeSpuRate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,float) ; 

__attribute__((used)) static void DecoderThread_ChangeRate( struct decoder_owner *p_owner, float rate )
{
    decoder_t *p_dec = &p_owner->dec;

    msg_Dbg( p_dec, "changing rate: %f", rate );
    vlc_mutex_lock( &p_owner->lock );
    switch( p_dec->fmt_out.i_cat )
    {
        case VIDEO_ES:
            if( p_owner->p_vout != NULL )
                vout_ChangeRate( p_owner->p_vout, rate );
            break;
        case AUDIO_ES:
            if( p_owner->p_aout != NULL )
                aout_DecChangeRate( p_owner->p_aout, rate );
            break;
        case SPU_ES:
            if( p_owner->p_vout != NULL )
            {
                assert(p_owner->i_spu_channel != VOUT_SPU_CHANNEL_INVALID);
                vout_ChangeSpuRate(p_owner->p_vout, p_owner->i_spu_channel,
                                   rate );
            }
            break;
        default:
            vlc_assert_unreachable();
    }
    p_owner->output_rate = rate;
    vlc_mutex_unlock( &p_owner->lock );
}