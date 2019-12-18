#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_6__ {int /*<<< orphan*/  i_cat; int /*<<< orphan*/  i_stream; void* i_fourcc; int /*<<< orphan*/  i_peek; void* i_type; int /*<<< orphan*/  i_pos; int /*<<< orphan*/  i_size; } ;
typedef  TYPE_2__ avi_packet_t ;

/* Variables and functions */
 void* AVIFOURCC_LIST ; 
 void* AVIFOURCC_RIFF ; 
 int /*<<< orphan*/  AVI_ParseStreamHeader (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDWLE (int /*<<< orphan*/  const*) ; 
 int VLC_EGENERIC ; 
 void* VLC_FOURCC (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int vlc_stream_Peek (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int) ; 
 int /*<<< orphan*/  vlc_stream_Tell (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int AVI_PacketGetHeader( demux_t *p_demux, avi_packet_t *p_pk )
{
    const uint8_t *p_peek;

    if( vlc_stream_Peek( p_demux->s, &p_peek, 16 ) < 16 )
    {
        return VLC_EGENERIC;
    }
    p_pk->i_fourcc  = VLC_FOURCC( p_peek[0], p_peek[1], p_peek[2], p_peek[3] );
    p_pk->i_size    = GetDWLE( p_peek + 4 );
    p_pk->i_pos     = vlc_stream_Tell( p_demux->s );
    if( p_pk->i_fourcc == AVIFOURCC_LIST || p_pk->i_fourcc == AVIFOURCC_RIFF )
    {
        p_pk->i_type = VLC_FOURCC( p_peek[8],  p_peek[9],
                                   p_peek[10], p_peek[11] );
    }
    else
    {
        p_pk->i_type = 0;
    }

    memcpy( p_pk->i_peek, p_peek + 8, 8 );

    AVI_ParseStreamHeader( p_pk->i_fourcc, &p_pk->i_stream, &p_pk->i_cat );
    return VLC_SUCCESS;
}