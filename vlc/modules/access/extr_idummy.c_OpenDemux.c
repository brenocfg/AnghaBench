#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_7__ {char* psz_location; void* pf_control; void* pf_demux; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_8__ {scalar_t__ length; scalar_t__ end; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 void* ControlPause ; 
 void* DemuxControl ; 
 void* DemuxHold ; 
 void* DemuxNoOp ; 
 void* DemuxPause ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  libvlc_Quit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,char const*) ; 
 int /*<<< orphan*/  msg_Info (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 
 int /*<<< orphan*/  strncasecmp (char const*,char*,int) ; 
 double us_atof (char const*) ; 
 TYPE_2__* vlc_obj_malloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_object_instance (TYPE_1__*) ; 
 scalar_t__ vlc_tick_from_sec (double) ; 
 scalar_t__ vlc_tick_now () ; 

__attribute__((used)) static int OpenDemux( vlc_object_t *p_this )
{
    demux_t *p_demux = (demux_t*)p_this;
    const char *psz_name = p_demux->psz_location;

    p_demux->p_sys = NULL;

    /* Check for a "vlc://nop" command */
    if( !strcasecmp( psz_name, "nop" ) )
    {
nop:
        msg_Info( p_demux, "command `nop'" );
        p_demux->pf_demux = DemuxNoOp;
        p_demux->pf_control = DemuxControl;
        return VLC_SUCCESS;
    }

    /* Check for a "vlc://quit" command */
    if( !strcasecmp( psz_name, "quit" ) )
    {
        msg_Info( p_demux, "command `quit'" );
        p_demux->pf_demux = DemuxNoOp;
        p_demux->pf_control = DemuxControl;
        libvlc_Quit( vlc_object_instance(p_demux) );
        return VLC_SUCCESS;
    }

    if( !strcasecmp( psz_name, "pause" ) )
    {
        msg_Info( p_demux, "command `pause'" );

        p_demux->pf_demux = DemuxHold;
        p_demux->pf_control = DemuxControl;
        return VLC_SUCCESS;
    }

    /* Check for a "vlc://pause:***" command */
    if( !strncasecmp( psz_name, "pause:", 6 ) )
    {
        double f = us_atof( psz_name + 6 );
        vlc_tick_t length = vlc_tick_from_sec( f );

        msg_Info( p_demux, "command `pause %f'", f );
        if( length == 0 )
            goto nop; /* avoid division by zero */

        demux_sys_t *p_sys = vlc_obj_malloc( p_this, sizeof( *p_sys ) );
        if( p_sys == NULL )
            return VLC_ENOMEM;

        p_sys->end = vlc_tick_now() + length;
        p_sys->length = length;

        p_demux->p_sys = p_sys;
        p_demux->pf_demux = DemuxPause;
        p_demux->pf_control = ControlPause;
        return VLC_SUCCESS;
    }

    msg_Err( p_demux, "unknown command `%s'", psz_name );
    return VLC_EGENERIC;
}