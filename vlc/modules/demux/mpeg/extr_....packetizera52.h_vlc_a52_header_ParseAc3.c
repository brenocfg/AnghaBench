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
struct TYPE_4__ {int i_dsurmod; } ;
struct vlc_a52_bitstream_info {size_t i_acmod; int i_frmsizcod; size_t i_fscod; int /*<<< orphan*/  i_bsid; scalar_t__ i_lfeon; TYPE_1__ ac3; } ;
struct TYPE_5__ {int i_bitrate; unsigned int i_rate; int i_size; int i_blocks_per_sync_frame; int i_samples; int b_eac3; int /*<<< orphan*/  i_channels_conf; int /*<<< orphan*/  i_channels; int /*<<< orphan*/  i_chan_mode; struct vlc_a52_bitstream_info bs; } ;
typedef  TYPE_2__ vlc_a52_header_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  AOUT_CHANMODE_DOLBYSTEREO ; 
 int /*<<< orphan*/  AOUT_CHANMODE_DUALMONO ; 
 int /*<<< orphan*/  AOUT_CHAN_LFE ; 
 scalar_t__ VLC_A52_MIN_HEADER_SIZE ; 
 int VLC_CLIP (int /*<<< orphan*/ ,int,int) ; 
 int VLC_EGENERIC ; 
 scalar_t__ VLC_SUCCESS ; 
 scalar_t__ vlc_a52_ParseAc3BitstreamInfo (struct vlc_a52_bitstream_info*,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  vlc_popcount (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int vlc_a52_header_ParseAc3( vlc_a52_header_t *p_header,
                                           const uint8_t *p_buf,
                                           const uint32_t *p_acmod,
                                           const unsigned *pi_fscod_samplerates )
{
    if( vlc_a52_ParseAc3BitstreamInfo( &p_header->bs,
                                       &p_buf[4], /* start code + CRC */
                                       VLC_A52_MIN_HEADER_SIZE - 4 ) != VLC_SUCCESS )
        return VLC_EGENERIC;

    /* cf. Table 5.18 Frame Size Code Table */
    static const uint16_t ppi_frmsizcod_fscod_sizes[][3] = {
        /* 32K, 44.1K, 48K */
        { 96, 69, 64 },
        { 96, 70, 64 },
        { 120, 87, 80 },
        { 120, 88, 80 },
        { 144, 104, 96 },
        { 144, 105, 96 },
        { 168, 121, 112 },
        { 168, 122, 112 },
        { 192, 139, 128 },
        { 192, 140, 128 },
        { 240, 174, 160 },
        { 240, 175, 160 },
        { 288, 208, 192 },
        { 288, 209, 192 },
        { 336, 243, 224 },
        { 336, 244, 224 },
        { 384, 278, 256 },
        { 384, 279, 256 },
        { 480, 348, 320 },
        { 480, 349, 320 },
        { 576, 417, 384 },
        { 576, 418, 384 },
        { 672, 487, 448 },
        { 672, 488, 448 },
        { 768, 557, 512 },
        { 768, 558, 512 },
        { 960, 696, 640 },
        { 960, 697, 640 },
        { 1152, 835, 768 },
        { 1152, 836, 768 },
        { 1344, 975, 896 },
        { 1344, 976, 896 },
        { 1536, 1114, 1024 },
        { 1536, 1115, 1024 },
        { 1728, 1253, 1152 },
        { 1728, 1254, 1152 },
        { 1920, 1393, 1280 },
        { 1920, 1394, 1280 }
    };
    static const uint16_t pi_frmsizcod_bitrates[] = {
        32,  40,  48,  56,
        64,  80,  96, 112,
        128, 160, 192, 224,
        256, 320, 384, 448,
        512, 576, 640
    };

    const struct vlc_a52_bitstream_info *bs = &p_header->bs;

    p_header->i_channels_conf = p_acmod[bs->i_acmod];
    p_header->i_chan_mode = 0;
    if( bs->ac3.i_dsurmod == 2 )
        p_header->i_chan_mode |= AOUT_CHANMODE_DOLBYSTEREO;
    if( bs->i_acmod == 0 )
        p_header->i_chan_mode |= AOUT_CHANMODE_DUALMONO;

    if( bs->i_lfeon )
        p_header->i_channels_conf |= AOUT_CHAN_LFE;

    p_header->i_channels = vlc_popcount(p_header->i_channels_conf);

    const unsigned i_rate_shift = VLC_CLIP(bs->i_bsid, 8, 11) - 8;
    p_header->i_bitrate = (pi_frmsizcod_bitrates[bs->i_frmsizcod >> 1] * 1000)
                        >> i_rate_shift;
    p_header->i_rate = pi_fscod_samplerates[bs->i_fscod] >> i_rate_shift;

    p_header->i_size = ppi_frmsizcod_fscod_sizes[bs->i_frmsizcod]
                                                [2 - bs->i_fscod] * 2;
    p_header->i_blocks_per_sync_frame = 6;
    p_header->i_samples = p_header->i_blocks_per_sync_frame * 256;

    p_header->b_eac3 = false;
    return VLC_SUCCESS;
}