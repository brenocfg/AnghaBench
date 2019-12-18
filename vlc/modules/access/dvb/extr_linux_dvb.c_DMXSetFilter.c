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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct dmx_pes_filter_params {int pid; int /*<<< orphan*/  pes_type; int /*<<< orphan*/  flags; int /*<<< orphan*/  output; int /*<<< orphan*/  input; } ;
typedef  int /*<<< orphan*/  dmx ;

/* Variables and functions */
 char* DMX ; 
 int /*<<< orphan*/  DMX_IMMEDIATE_START ; 
 int /*<<< orphan*/  DMX_IN_FRONTEND ; 
 int /*<<< orphan*/  DMX_OUT_TS_TAP ; 
 int /*<<< orphan*/  DMX_PES_AUDIO0 ; 
 int /*<<< orphan*/  DMX_PES_AUDIO1 ; 
 int /*<<< orphan*/  DMX_PES_AUDIO2 ; 
 int /*<<< orphan*/  DMX_PES_AUDIO3 ; 
 int /*<<< orphan*/  DMX_PES_OTHER ; 
 int /*<<< orphan*/  DMX_PES_PCR0 ; 
 int /*<<< orphan*/  DMX_PES_PCR1 ; 
 int /*<<< orphan*/  DMX_PES_PCR2 ; 
 int /*<<< orphan*/  DMX_PES_PCR3 ; 
 int /*<<< orphan*/  DMX_PES_SUBTITLE0 ; 
 int /*<<< orphan*/  DMX_PES_SUBTITLE1 ; 
 int /*<<< orphan*/  DMX_PES_SUBTITLE2 ; 
 int /*<<< orphan*/  DMX_PES_SUBTITLE3 ; 
 int /*<<< orphan*/  DMX_PES_TELETEXT0 ; 
 int /*<<< orphan*/  DMX_PES_TELETEXT1 ; 
 int /*<<< orphan*/  DMX_PES_TELETEXT2 ; 
 int /*<<< orphan*/  DMX_PES_TELETEXT3 ; 
 int /*<<< orphan*/  DMX_PES_VIDEO0 ; 
 int /*<<< orphan*/  DMX_PES_VIDEO1 ; 
 int /*<<< orphan*/  DMX_PES_VIDEO2 ; 
 int /*<<< orphan*/  DMX_PES_VIDEO3 ; 
 int /*<<< orphan*/  DMX_SET_PES_FILTER ; 
 int /*<<< orphan*/  O_RDWR ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct dmx_pes_filter_params*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,...) ; 
 int snprintf (char*,int,char*,unsigned int,unsigned int) ; 
 unsigned int var_GetInteger (int /*<<< orphan*/ *,char*) ; 
 int vlc_open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_strerror_c (int /*<<< orphan*/ ) ; 

int DMXSetFilter( vlc_object_t *p_access, int i_pid, int * pi_fd, int i_type )
{
    struct dmx_pes_filter_params s_filter_params;
    unsigned int i_adapter, i_device;
    char dmx[128];

    i_adapter = var_GetInteger( p_access, "dvb-adapter" );
    i_device = var_GetInteger( p_access, "dvb-device" );

    if( snprintf( dmx, sizeof(dmx), DMX, i_adapter, i_device )
            >= (int)sizeof(dmx) )
    {
        msg_Err( p_access, "snprintf() truncated string for DMX" );
        dmx[sizeof(dmx) - 1] = '\0';
    }

    msg_Dbg( p_access, "Opening device %s", dmx );
    if( (*pi_fd = vlc_open(dmx, O_RDWR)) < 0 )
    {
        msg_Err( p_access, "DMXSetFilter: opening device failed: %s",
                 vlc_strerror_c(errno) );
        return VLC_EGENERIC;
    }

    /* We fill the DEMUX structure : */
    s_filter_params.pid     =   i_pid;
    s_filter_params.input   =   DMX_IN_FRONTEND;
    s_filter_params.output  =   DMX_OUT_TS_TAP;
    s_filter_params.flags   =   DMX_IMMEDIATE_START;

    switch ( i_type )
    {   /* First device */
        case 1:
            msg_Dbg(p_access, "DMXSetFilter: DMX_PES_VIDEO0 for PID %d", i_pid);
            s_filter_params.pes_type = DMX_PES_VIDEO0;
            break;
        case 2:
            msg_Dbg(p_access, "DMXSetFilter: DMX_PES_AUDIO0 for PID %d", i_pid);
            s_filter_params.pes_type = DMX_PES_AUDIO0;
            break;
        case 3:
            msg_Dbg(p_access, "DMXSetFilter: DMX_PES_TELETEXT0 for PID %d", i_pid);
            s_filter_params.pes_type = DMX_PES_TELETEXT0;
            break;
        case 4:
            msg_Dbg(p_access, "DMXSetFilter: DMX_PES_SUBTITLE0 for PID %d", i_pid);
            s_filter_params.pes_type = DMX_PES_SUBTITLE0;
            break;
        case 5:
            msg_Dbg(p_access, "DMXSetFilter: DMX_PES_PCR0 for PID %d", i_pid);
            s_filter_params.pes_type = DMX_PES_PCR0;
            break;
        /* Second device */
        case 6:
            msg_Dbg(p_access, "DMXSetFilter: DMX_PES_VIDEO1 for PID %d", i_pid);
            s_filter_params.pes_type = DMX_PES_VIDEO1;
            break;
        case 7:
            msg_Dbg(p_access, "DMXSetFilter: DMX_PES_AUDIO1 for PID %d", i_pid);
            s_filter_params.pes_type = DMX_PES_AUDIO1;
            break;
        case 8:
            msg_Dbg(p_access, "DMXSetFilter: DMX_PES_TELETEXT1 for PID %d", i_pid);
            s_filter_params.pes_type = DMX_PES_TELETEXT1;
            break;
        case 9:
            msg_Dbg(p_access, "DMXSetFilter: DMX_PES_SUBTITLE1 for PID %d", i_pid);
            s_filter_params.pes_type = DMX_PES_SUBTITLE1;
            break;
        case 10:
            msg_Dbg(p_access, "DMXSetFilter: DMX_PES_PCR1 for PID %d", i_pid);
            s_filter_params.pes_type = DMX_PES_PCR1;
            break;
        /* Third device */
        case 11:
            msg_Dbg(p_access, "DMXSetFilter: DMX_PES_VIDEO2 for PID %d", i_pid);
            s_filter_params.pes_type = DMX_PES_VIDEO2;
            break;
        case 12:
            msg_Dbg(p_access, "DMXSetFilter: DMX_PES_AUDIO2 for PID %d", i_pid);
            s_filter_params.pes_type = DMX_PES_AUDIO2;
            break;
        case 13:
            msg_Dbg(p_access, "DMXSetFilter: DMX_PES_TELETEXT2 for PID %d", i_pid);
            s_filter_params.pes_type = DMX_PES_TELETEXT2;
            break;
        case 14:
            msg_Dbg(p_access, "DMXSetFilter: DMX_PES_SUBTITLE2 for PID %d", i_pid);
            s_filter_params.pes_type = DMX_PES_SUBTITLE2;
            break;
        case 15:
            msg_Dbg(p_access, "DMXSetFilter: DMX_PES_PCR2 for PID %d", i_pid);
            s_filter_params.pes_type = DMX_PES_PCR2;
            break;
        /* Forth device */
        case 16:
            msg_Dbg(p_access, "DMXSetFilter: DMX_PES_VIDEO3 for PID %d", i_pid);
            s_filter_params.pes_type = DMX_PES_VIDEO3;
            break;
        case 17:
            msg_Dbg(p_access, "DMXSetFilter: DMX_PES_AUDIO3 for PID %d", i_pid);
            s_filter_params.pes_type = DMX_PES_AUDIO3;
            break;
        case 18:
            msg_Dbg(p_access, "DMXSetFilter: DMX_PES_TELETEXT3 for PID %d", i_pid);
            s_filter_params.pes_type = DMX_PES_TELETEXT3;
            break;
        case 19:
            msg_Dbg(p_access, "DMXSetFilter: DMX_PES_SUBTITLE3 for PID %d", i_pid);
            s_filter_params.pes_type = DMX_PES_SUBTITLE3;
            break;
        case 20:
            msg_Dbg(p_access, "DMXSetFilter: DMX_PES_PCR3 for PID %d", i_pid);
            s_filter_params.pes_type = DMX_PES_PCR3;
            break;
        /* Usually used by Nova cards */
        case 21:
        default:
            msg_Dbg(p_access, "DMXSetFilter: DMX_PES_OTHER for PID %d", i_pid);
            s_filter_params.pes_type = DMX_PES_OTHER;
            break;
    }

    /* We then give the order to the device : */
    if( ioctl( *pi_fd, DMX_SET_PES_FILTER, &s_filter_params ) )
    {
        msg_Err( p_access, "setting demux PES filter failed: %s",
                 vlc_strerror_c(errno) );
        return VLC_EGENERIC;
    }
    return VLC_SUCCESS;
}