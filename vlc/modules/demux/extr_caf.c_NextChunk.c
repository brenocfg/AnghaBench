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
typedef  int /*<<< orphan*/  vlc_fourcc_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ demux_t ;

/* Variables and functions */
 scalar_t__ GetQWBE (int /*<<< orphan*/ *) ; 
 scalar_t__ INT64_MAX ; 
 int /*<<< orphan*/  ReadFOURCC (int /*<<< orphan*/ *) ; 
 scalar_t__ UINT64_C (int) ; 
 int VLC_EGENERIC ; 
 int /*<<< orphan*/  VLC_FOURCC (char,char,char,char) ; 
 int VLC_SUCCESS ; 
 scalar_t__ kCHUNK_SIZE_EOF ; 
 int vlc_stream_Read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int NextChunk( demux_t *p_demux, vlc_fourcc_t *p_fcc, uint64_t *pi_size )
{
    uint8_t p_read[12];

    if( vlc_stream_Read( p_demux->s, p_read, 12 ) < 12 )
        return VLC_EGENERIC;

    *p_fcc = ReadFOURCC( p_read );
    uint64_t i_size = GetQWBE( p_read + 4 );

    /* We accept no negativ sizes for chunks, except -1 for the data chunk. */

    if( i_size > INT64_MAX )
    {
        if( *p_fcc == VLC_FOURCC( 'd', 'a', 't', 'a' ) && i_size == UINT64_C( -1 ))
            i_size = kCHUNK_SIZE_EOF;
        else
            return VLC_EGENERIC;
    }

    *pi_size = i_size;

    return VLC_SUCCESS;
}