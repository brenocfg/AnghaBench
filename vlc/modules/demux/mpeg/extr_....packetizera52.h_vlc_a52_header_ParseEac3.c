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
struct TYPE_4__ {int i_frmsiz; size_t i_fscod2; size_t i_numblkscod; } ;
struct vlc_a52_bitstream_info {int i_fscod; size_t i_acmod; scalar_t__ i_lfeon; TYPE_1__ eac3; } ;
struct TYPE_5__ {int i_size; unsigned int i_rate; int i_blocks_per_sync_frame; int i_bitrate; int i_samples; int b_eac3; int /*<<< orphan*/  i_channels_conf; int /*<<< orphan*/  i_channels; int /*<<< orphan*/  i_chan_mode; struct vlc_a52_bitstream_info bs; } ;
typedef  TYPE_2__ vlc_a52_header_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  AOUT_CHANMODE_DUALMONO ; 
 int /*<<< orphan*/  AOUT_CHAN_LFE ; 
 scalar_t__ VLC_A52_MIN_HEADER_SIZE ; 
 int VLC_EGENERIC ; 
 scalar_t__ VLC_SUCCESS ; 
 scalar_t__ vlc_a52_ParseEac3BitstreamInfo (struct vlc_a52_bitstream_info*,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  vlc_popcount (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int vlc_a52_header_ParseEac3( vlc_a52_header_t *p_header,
                                            const uint8_t *p_buf,
                                            const uint32_t *p_acmod,
                                            const unsigned *pi_fscod_samplerates )
{
    if( vlc_a52_ParseEac3BitstreamInfo( &p_header->bs,
                                        &p_buf[2], /* start code */
                                        VLC_A52_MIN_HEADER_SIZE - 2 ) != VLC_SUCCESS )
        return VLC_EGENERIC;

    const struct vlc_a52_bitstream_info *bs = &p_header->bs;

    p_header->i_size = 2 * (bs->eac3.i_frmsiz + 1 );

    if( bs->i_fscod == 0x03 )
    {
        p_header->i_rate = pi_fscod_samplerates[bs->eac3.i_fscod2] / 2;
        p_header->i_blocks_per_sync_frame = 6;
    }
    else
    {
        static const int pi_numblkscod [4] = { 1, 2, 3, 6 };
        p_header->i_rate = pi_fscod_samplerates[bs->i_fscod];
        p_header->i_blocks_per_sync_frame = pi_numblkscod[bs->eac3.i_numblkscod];
    }

    p_header->i_channels_conf = p_acmod[bs->i_acmod];
    p_header->i_chan_mode = 0;
    if( bs->i_acmod == 0 )
        p_header->i_chan_mode |= AOUT_CHANMODE_DUALMONO;
    if( bs->i_lfeon )
        p_header->i_channels_conf |= AOUT_CHAN_LFE;
    p_header->i_channels = vlc_popcount( p_header->i_channels_conf );
    p_header->i_bitrate = 8 * p_header->i_size * p_header->i_rate
                        / (p_header->i_blocks_per_sync_frame * 256);
    p_header->i_samples = p_header->i_blocks_per_sync_frame * 256;

    p_header->b_eac3 = true;
    return VLC_SUCCESS;
}