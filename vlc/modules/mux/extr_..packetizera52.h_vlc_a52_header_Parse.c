#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_a52_header_t ;
typedef  int uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
#define  AOUT_CHANS_2_0 135 
#define  AOUT_CHANS_3_0 134 
#define  AOUT_CHANS_4_0 133 
#define  AOUT_CHANS_5_0 132 
#define  AOUT_CHANS_CENTER 131 
#define  AOUT_CHANS_FRONT 130 
#define  AOUT_CHAN_CENTER 129 
#define  AOUT_CHAN_REARCENTER 128 
 int VLC_A52_MIN_HEADER_SIZE ; 
 int VLC_EGENERIC ; 
 int vlc_a52_header_ParseAc3 (int /*<<< orphan*/ *,int const*,int const*,unsigned int const*) ; 
 int vlc_a52_header_ParseEac3 (int /*<<< orphan*/ *,int const*,int const*,unsigned int const*) ; 

__attribute__((used)) static inline int vlc_a52_header_Parse( vlc_a52_header_t *p_header,
                                        const uint8_t *p_buffer, int i_buffer )
{
    static const uint32_t p_acmod[8] = {
        AOUT_CHANS_2_0,
        AOUT_CHAN_CENTER,
        AOUT_CHANS_2_0,
        AOUT_CHANS_3_0,
        AOUT_CHANS_FRONT | AOUT_CHAN_REARCENTER, /* 2F1R */
        AOUT_CHANS_FRONT | AOUT_CHANS_CENTER,    /* 3F1R */
        AOUT_CHANS_4_0,
        AOUT_CHANS_5_0,
    };
    static const unsigned pi_fscod_samplerates[] = {
        48000, 44100, 32000
    };

    if( i_buffer < VLC_A52_MIN_HEADER_SIZE )
        return VLC_EGENERIC;

    /* Check synword */
    if( p_buffer[0] != 0x0b || p_buffer[1] != 0x77 )
        return VLC_EGENERIC;

    /* Check bsid */
    const int bsid = p_buffer[5] >> 3;

    /* cf. Annex E 2.3.1.6 of AC3 spec */
    if( bsid <= 10 )
        return vlc_a52_header_ParseAc3( p_header, p_buffer,
                                        p_acmod, pi_fscod_samplerates );
    else if( bsid <= 16 )
        return vlc_a52_header_ParseEac3( p_header, p_buffer,
                                         p_acmod, pi_fscod_samplerates );
    else
        return VLC_EGENERIC;
}