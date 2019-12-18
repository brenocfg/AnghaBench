#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_fourcc_t ;
typedef  int uint64_t ;
struct TYPE_3__ {int i_608_channels; int i_708_channels; } ;
struct TYPE_4__ {TYPE_1__ desc; } ;
struct decoder_owner {TYPE_2__ cc; } ;

/* Variables and functions */
 scalar_t__ VLC_CODEC_CEA608 ; 
 scalar_t__ VLC_CODEC_CEA708 ; 

__attribute__((used)) static bool input_DecoderHasCCChanFlag( struct decoder_owner *p_owner,
                                        vlc_fourcc_t codec, int i_channel )
{
    int i_max_channels;
    uint64_t i_bitmap;
    if( codec == VLC_CODEC_CEA608 )
    {
        i_max_channels = 4;
        i_bitmap = p_owner->cc.desc.i_608_channels;
    }
    else if( codec == VLC_CODEC_CEA708 )
    {
        i_max_channels = 64;
        i_bitmap = p_owner->cc.desc.i_708_channels;
    }
    else return false;

    return ( i_channel >= 0 && i_channel < i_max_channels &&
             ( i_bitmap & ((uint64_t)1 << i_channel) ) );
}