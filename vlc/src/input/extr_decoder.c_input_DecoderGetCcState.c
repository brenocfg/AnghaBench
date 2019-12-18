#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_fourcc_t ;
struct TYPE_2__ {int /*<<< orphan*/ ** pp_decoder; } ;
struct decoder_owner {int /*<<< orphan*/  lock; TYPE_1__ cc; } ;
typedef  int /*<<< orphan*/  decoder_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 struct decoder_owner* dec_get_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_DecoderHasCCChanFlag (struct decoder_owner*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

int input_DecoderGetCcState( decoder_t *p_dec, vlc_fourcc_t codec,
                             int i_channel, bool *pb_decode )
{
    struct decoder_owner *p_owner = dec_get_owner( p_dec );

    if( !input_DecoderHasCCChanFlag( p_owner, codec, i_channel ) )
        return VLC_EGENERIC;

    vlc_mutex_lock( &p_owner->lock );
    *pb_decode = p_owner->cc.pp_decoder[i_channel] != NULL;
    vlc_mutex_unlock( &p_owner->lock );
    return VLC_SUCCESS;
}