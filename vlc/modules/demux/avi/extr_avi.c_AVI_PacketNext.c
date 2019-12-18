#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
struct TYPE_6__ {int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_7__ {scalar_t__ i_fourcc; scalar_t__ i_type; int i_size; } ;
typedef  TYPE_2__ avi_packet_t ;

/* Variables and functions */
 scalar_t__ AVIFOURCC_AVIX ; 
 scalar_t__ AVIFOURCC_LIST ; 
 scalar_t__ AVIFOURCC_RIFF ; 
 scalar_t__ AVIFOURCC_movi ; 
 scalar_t__ AVIFOURCC_rec ; 
 scalar_t__ AVI_PacketGetHeader (TYPE_1__*,TYPE_2__*) ; 
 size_t SSIZE_MAX ; 
 int UINT32_MAX ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int __EVEN (int) ; 
 scalar_t__ vlc_stream_Read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int AVI_PacketNext( demux_t *p_demux )
{
    avi_packet_t    avi_ck;
    size_t          i_skip = 0;

    if( AVI_PacketGetHeader( p_demux, &avi_ck ) )
    {
        return VLC_EGENERIC;
    }

    if( avi_ck.i_fourcc == AVIFOURCC_LIST &&
        ( avi_ck.i_type == AVIFOURCC_rec || avi_ck.i_type == AVIFOURCC_movi ) )
    {
        i_skip = 12;
    }
    else if( avi_ck.i_fourcc == AVIFOURCC_RIFF &&
             avi_ck.i_type == AVIFOURCC_AVIX )
    {
        i_skip = 24;
    }
    else
    {
        if( avi_ck.i_size > UINT32_MAX - 9 )
            return VLC_EGENERIC;
        i_skip = __EVEN( avi_ck.i_size ) + 8;
    }

    if( i_skip > SSIZE_MAX )
        return VLC_EGENERIC;

    ssize_t i_ret = vlc_stream_Read( p_demux->s, NULL, i_skip );
    if( i_ret < 0 || (size_t) i_ret != i_skip )
    {
        return VLC_EGENERIC;
    }
    return VLC_SUCCESS;
}