#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  vlc_guid_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {TYPE_3__* p_sys; int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_demux; int /*<<< orphan*/  s; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_7__ {int /*<<< orphan*/  pf_setaspectratio; int /*<<< orphan*/  pf_updatesendtime; int /*<<< orphan*/  pf_updatetime; int /*<<< orphan*/  pf_gettrackinfo; int /*<<< orphan*/  pf_send; int /*<<< orphan*/  pf_doskip; TYPE_2__* p_demux; } ;
struct TYPE_9__ {TYPE_1__ packet_sys; } ;
typedef  TYPE_3__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASF_GetGUID (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  Control ; 
 int /*<<< orphan*/  Demux ; 
 scalar_t__ DemuxInit (TYPE_2__*) ; 
 int /*<<< orphan*/  Packet_DoSkip ; 
 int /*<<< orphan*/  Packet_Enqueue ; 
 int /*<<< orphan*/  Packet_GetTrackInfo ; 
 int /*<<< orphan*/  Packet_SetAR ; 
 int /*<<< orphan*/  Packet_SetSendTime ; 
 int /*<<< orphan*/  Packet_UpdateTime ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  asf_object_header_guid ; 
 TYPE_3__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  guidcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int vlc_stream_Peek (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int) ; 

__attribute__((used)) static int Open( vlc_object_t * p_this )
{
    demux_t     *p_demux = (demux_t *)p_this;
    demux_sys_t *p_sys;
    vlc_guid_t      guid;
    const uint8_t     *p_peek;

    /* A little test to see if it could be a asf stream */
    if( vlc_stream_Peek( p_demux->s, &p_peek, 16 ) < 16 ) return VLC_EGENERIC;

    ASF_GetGUID( &guid, p_peek );
    if( !guidcmp( &guid, &asf_object_header_guid ) ) return VLC_EGENERIC;

    /* Set p_demux fields */
    p_demux->pf_demux = Demux;
    p_demux->pf_control = Control;
    p_demux->p_sys = p_sys = calloc( 1, sizeof( demux_sys_t ) );

    /* Load the headers */
    if( DemuxInit( p_demux ) )
    {
        free( p_sys );
        return VLC_EGENERIC;
    }

    p_sys->packet_sys.p_demux = p_demux;
    p_sys->packet_sys.pf_doskip = Packet_DoSkip;
    p_sys->packet_sys.pf_send = Packet_Enqueue;
    p_sys->packet_sys.pf_gettrackinfo = Packet_GetTrackInfo;
    p_sys->packet_sys.pf_updatetime = Packet_UpdateTime;
    p_sys->packet_sys.pf_updatesendtime = Packet_SetSendTime;
    p_sys->packet_sys.pf_setaspectratio = Packet_SetAR;

    return VLC_SUCCESS;
}