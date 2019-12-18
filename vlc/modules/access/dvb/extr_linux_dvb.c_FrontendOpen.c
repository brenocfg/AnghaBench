#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_8__ {int type; } ;
struct TYPE_9__ {TYPE_1__ info; } ;
typedef  TYPE_2__ frontend_t ;
typedef  int /*<<< orphan*/  frontend ;
struct TYPE_10__ {int /*<<< orphan*/  i_frontend_handle; TYPE_2__* p_frontend; } ;
typedef  TYPE_3__ dvb_sys_t ;

/* Variables and functions */
#define  FE_ATSC 131 
#define  FE_OFDM 130 
#define  FE_QAM 129 
#define  FE_QPSK 128 
 char* FRONTEND ; 
 scalar_t__ FrontendInfo (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int O_NONBLOCK ; 
 int O_RDWR ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,...) ; 
 int snprintf (char*,int,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 int var_GetBool (int /*<<< orphan*/ *,char*) ; 
 unsigned int var_GetInteger (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vlc_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_open (char*,int) ; 
 int /*<<< orphan*/  vlc_strerror_c (int /*<<< orphan*/ ) ; 

int FrontendOpen( vlc_object_t *p_access, dvb_sys_t *p_sys, const char *psz_access )
{
    frontend_t * p_frontend;
    unsigned int i_adapter, i_device;
    bool b_probe;
    char frontend[128];

    i_adapter = var_GetInteger( p_access, "dvb-adapter" );
    i_device = var_GetInteger( p_access, "dvb-device" );
    b_probe = var_GetBool( p_access, "dvb-probe" );

    if( snprintf( frontend, sizeof(frontend), FRONTEND, i_adapter, i_device ) >= (int)sizeof(frontend) )
    {
        msg_Err( p_access, "snprintf() truncated string for FRONTEND" );
        frontend[sizeof(frontend) - 1] = '\0';
    }

    p_sys->p_frontend = p_frontend = malloc( sizeof(frontend_t) );
    if( !p_frontend )
        return VLC_ENOMEM;

    msg_Dbg( p_access, "Opening device %s", frontend );
    if( (p_sys->i_frontend_handle = vlc_open(frontend, O_RDWR | O_NONBLOCK)) < 0 )
    {
        msg_Err( p_access, "FrontEndOpen: opening device failed: %s",
                 vlc_strerror_c(errno) );
        free( p_frontend );
        return VLC_EGENERIC;
    }

    if( b_probe )
    {
        const char * psz_expected = NULL;
        const char * psz_real;

        if( FrontendInfo( p_access, p_sys ) < 0 )
        {
            vlc_close( p_sys->i_frontend_handle );
            free( p_frontend );
            return VLC_EGENERIC;
        }

        switch( p_frontend->info.type )
        {
        case FE_OFDM:
            psz_real = "DVB-T";
            break;
        case FE_QAM:
            psz_real = "DVB-C";
            break;
        case FE_QPSK:
            psz_real = "DVB-S";
            break;
        case FE_ATSC:
            psz_real = "ATSC";
            break;
        default:
            psz_real = "unknown";
        }

        /* Sanity checks */
        if( (!strncmp( psz_access, "qpsk", 4 ) ||
             !strncmp( psz_access, "dvb-s", 5 ) ||
             !strncmp( psz_access, "satellite", 9 ) ) &&
             (p_frontend->info.type != FE_QPSK) )
        {
            psz_expected = "DVB-S";
        }
        if( (!strncmp( psz_access, "cable", 5 ) ||
             !strncmp( psz_access, "dvb-c", 5 ) ) &&
             (p_frontend->info.type != FE_QAM) )
        {
            psz_expected = "DVB-C";
        }
        if( (!strncmp( psz_access, "terrestrial", 11 ) ||
             !strncmp( psz_access, "dvb-t", 5 ) ) &&
             (p_frontend->info.type != FE_OFDM) )
        {
            psz_expected = "DVB-T";
        }

        if( (!strncmp( psz_access, "usdigital", 9 ) ||
             !strncmp( psz_access, "atsc", 4 ) ) &&
             (p_frontend->info.type != FE_ATSC) )
        {
            psz_expected = "ATSC";
        }

        if( psz_expected != NULL )
        {
            msg_Err( p_access, "requested type %s not supported by %s tuner",
                     psz_expected, psz_real );
            vlc_close( p_sys->i_frontend_handle );
            free( p_frontend );
            return VLC_EGENERIC;
        }
    }
    else /* no frontend probing is done so use default border values. */
    {
        msg_Dbg( p_access, "using default values for frontend info" );

        msg_Dbg( p_access, "method of access is %s", psz_access );
        p_frontend->info.type = FE_QPSK;
        if( !strncmp( psz_access, "qpsk", 4 ) ||
            !strncmp( psz_access, "dvb-s", 5 ) )
            p_frontend->info.type = FE_QPSK;
        else if( !strncmp( psz_access, "cable", 5 ) ||
                 !strncmp( psz_access, "dvb-c", 5 ) )
            p_frontend->info.type = FE_QAM;
        else if( !strncmp( psz_access, "terrestrial", 11 ) ||
                 !strncmp( psz_access, "dvb-t", 5 ) )
            p_frontend->info.type = FE_OFDM;
        else if( !strncmp( psz_access, "usdigital", 9 ) ||
                 !strncmp( psz_access, "atsc", 4 ) )
            p_frontend->info.type = FE_ATSC;
    }

    return VLC_SUCCESS;
}