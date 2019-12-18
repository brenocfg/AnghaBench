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
struct TYPE_3__ {int i_frame_size; scalar_t__ syncword; int i_frame_length; int /*<<< orphan*/  i_physical_channels; int /*<<< orphan*/  i_rate; int /*<<< orphan*/  i_chan_mode; int /*<<< orphan*/  i_bitrate; } ;
typedef  TYPE_1__ vlc_dts_header_t ;
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  bs_t ;

/* Variables and functions */
 scalar_t__ DTS_SYNC_CORE_14BITS_BE ; 
 scalar_t__ DTS_SYNC_CORE_14BITS_LE ; 
 int /*<<< orphan*/  VLC_DTS_HEADER_SIZE ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  bs_init (int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ ) ; 
 int bs_read (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bs_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dca_get_bitrate (int) ; 
 int /*<<< orphan*/  dca_get_channels (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dca_get_samplerate (int) ; 

__attribute__((used)) static int dts_header_ParseCore( vlc_dts_header_t *p_header,
                                 const void *p_buffer)
{
    bs_t s;
    bs_init( &s, p_buffer, VLC_DTS_HEADER_SIZE );
    bs_skip( &s, 32 /*SYNC*/ + 1 /*FTYPE*/ + 5 /*SHORT*/ + 1 /*CPF*/ );
    uint8_t i_nblks = bs_read( &s, 7 );
    if( i_nblks < 5 )
        return VLC_EGENERIC;
    uint16_t i_fsize = bs_read( &s, 14 );
    if( i_fsize < 95 )
        return VLC_EGENERIC;
    uint8_t i_amode = bs_read( &s, 6 );
    uint8_t i_sfreq = bs_read( &s, 4 );
    uint8_t i_rate = bs_read( &s, 5 );
    bs_skip( &s, 1 /*FixedBit*/ + 1 /*DYNF*/ + 1 /*TIMEF*/ + 1 /*AUXF*/ +
             1 /*HDCD*/ + 3 /*EXT_AUDIO_ID*/ + 1 /*EXT_AUDIO */ + 1 /*ASPF*/ );
    uint8_t i_lff = bs_read( &s, 2 );

    bool b_lfe = i_lff == 1 || i_lff == 2;

    p_header->i_rate = dca_get_samplerate( i_sfreq );
    p_header->i_bitrate = dca_get_bitrate( i_rate );
    p_header->i_frame_size = i_fsize + 1;
    if( p_header->syncword == DTS_SYNC_CORE_14BITS_LE ||
        p_header->syncword == DTS_SYNC_CORE_14BITS_BE )
        p_header->i_frame_size = p_header->i_frame_size * 16 / 14;
    /* See ETSI TS 102 114, table 5-2 */
    p_header->i_frame_length = (i_nblks + 1) * 32;
    p_header->i_chan_mode = 0;
    p_header->i_physical_channels =
        dca_get_channels( i_amode, b_lfe, &p_header->i_chan_mode );

    if( !p_header->i_rate || !p_header->i_frame_size ||
        !p_header->i_frame_length || !p_header->i_physical_channels )
        return VLC_EGENERIC;

    return VLC_SUCCESS;
}