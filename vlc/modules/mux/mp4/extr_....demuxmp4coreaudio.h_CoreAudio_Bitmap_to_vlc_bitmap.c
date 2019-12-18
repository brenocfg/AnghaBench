#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct CoreAudio_layout_s {int i_channels_bitmap; } ;
struct TYPE_3__ {int i_bitmap; int i_vlc_bitmap; } ;

/* Variables and functions */
 size_t AOUT_CHAN_MAX ; 
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* CoreAudio_Bitmap_mapping ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/ * pi_vlc_chan_order_CoreAudio ; 

__attribute__((used)) static inline int CoreAudio_Bitmap_to_vlc_bitmap( const struct CoreAudio_layout_s *c,
                                                  uint16_t *pi_mapping,
                                                  uint8_t *pi_channels,
                                                  const uint32_t **pp_chans_order )
{
    *pp_chans_order = pi_vlc_chan_order_CoreAudio;
    *pi_mapping = 0;
    *pi_channels = 0;
    for (uint8_t i=0;i<ARRAY_SIZE(CoreAudio_Bitmap_mapping);i++)
    {
        if ( CoreAudio_Bitmap_mapping[i].i_bitmap & c->i_channels_bitmap )
        {
            if ( (CoreAudio_Bitmap_mapping[i].i_vlc_bitmap & *pi_mapping) ||
                 *pi_channels >= AOUT_CHAN_MAX )
            {
                /* double mapping or unsupported number of channels */
                *pi_mapping = 0;
                *pi_channels = 0;
                return VLC_EGENERIC;
            }
            *pi_mapping |= CoreAudio_Bitmap_mapping[i].i_vlc_bitmap;
        }
    }
    return VLC_SUCCESS;
}