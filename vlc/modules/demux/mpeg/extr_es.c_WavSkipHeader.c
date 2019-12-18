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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint64_t ;
typedef  int /*<<< orphan*/  const* uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  int ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ demux_t ;

/* Variables and functions */
 int /*<<< orphan*/ * GetDWLE (int /*<<< orphan*/  const*) ; 
 scalar_t__ GetWLE (int) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ const WAVE_FORMAT_UNKNOWN ; 
 int /*<<< orphan*/  const* WAV_PROBE_SIZE ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,char*,int) ; 
 int vlc_stream_Peek (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,size_t) ; 

__attribute__((used)) static int WavSkipHeader( demux_t *p_demux, uint64_t *pi_skip,
                          const uint16_t rgi_twocc[],
                          int (*pf_format_check)( int, const uint8_t * ) )
{
    const uint8_t *p_peek;
    size_t i_peek = 0;
    uint32_t i_len;

    /* */
    *pi_skip = 0;

    /* Check if we are dealing with a WAV file */
    if( vlc_stream_Peek( p_demux->s, &p_peek, 12+8 ) != 12 + 8 )
        return VLC_SUCCESS;

    if( memcmp( p_peek, "RIFF", 4 ) || memcmp( &p_peek[8], "WAVE", 4 ) )
        return VLC_SUCCESS;

    /* Find the wave format header */
    i_peek = 12 + 8;
    while( memcmp( p_peek + i_peek - 8, "fmt ", 4 ) )
    {
        i_len = GetDWLE( p_peek + i_peek - 4 );
        if( i_len > WAV_PROBE_SIZE || i_peek + i_len > WAV_PROBE_SIZE )
            return VLC_EGENERIC;

        i_peek += i_len + 8;
        if( vlc_stream_Peek( p_demux->s, &p_peek, i_peek ) != (ssize_t) i_peek )
            return VLC_EGENERIC;
    }

    /* Sanity check the wave format header */
    i_len = GetDWLE( p_peek + i_peek - 4 );
    if( i_len > WAV_PROBE_SIZE )
        return VLC_EGENERIC;

    i_peek += i_len + 8;
    if( vlc_stream_Peek( p_demux->s, &p_peek, i_peek ) != (ssize_t) i_peek )
        return VLC_EGENERIC;
    const uint16_t i_twocc = GetWLE( p_peek + i_peek - i_len - 8 /* wFormatTag */ );
    int i_format_idx;
    for( i_format_idx = 0; rgi_twocc[i_format_idx] != WAVE_FORMAT_UNKNOWN; i_format_idx++ )
    {
        if( i_twocc == rgi_twocc[i_format_idx] )
            break;
    }
    if( rgi_twocc[i_format_idx] == WAVE_FORMAT_UNKNOWN )
        return VLC_EGENERIC;

    if( pf_format_check &&
        pf_format_check( i_twocc, p_peek + i_peek - i_len - 6 ) != VLC_SUCCESS )
            return VLC_EGENERIC;

    /* Skip the wave header */
    while( memcmp( p_peek + i_peek - 8, "data", 4 ) )
    {
        i_len = GetDWLE( p_peek + i_peek - 4 );
        if( i_len > WAV_PROBE_SIZE || i_peek + i_len > WAV_PROBE_SIZE )
            return VLC_EGENERIC;

        i_peek += i_len + 8;
        if( vlc_stream_Peek( p_demux->s, &p_peek, i_peek ) != (ssize_t) i_peek )
            return VLC_EGENERIC;
    }
    *pi_skip = i_peek;
    return VLC_SUCCESS;
}