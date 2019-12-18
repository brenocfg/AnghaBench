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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  dvr ;
struct TYPE_3__ {int /*<<< orphan*/  i_handle; } ;
typedef  TYPE_1__ dvb_sys_t ;

/* Variables and functions */
 char* DVR ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  errno ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,unsigned int,unsigned int) ; 
 unsigned int var_GetInteger (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vlc_open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_strerror_c (int /*<<< orphan*/ ) ; 

int DVROpen( vlc_object_t *p_access, dvb_sys_t *p_sys )
{
    unsigned int i_adapter, i_device;
    char dvr[128];

    i_adapter = var_GetInteger( p_access, "dvb-adapter" );
    i_device = var_GetInteger( p_access, "dvb-device" );

    if( snprintf( dvr, sizeof(dvr), DVR, i_adapter, i_device )
            >= (int)sizeof(dvr) )
    {
        msg_Err( p_access, "snprintf() truncated string for DVR" );
        dvr[sizeof(dvr) - 1] = '\0';
    }

    msg_Dbg( p_access, "Opening device %s", dvr );
    if( (p_sys->i_handle = vlc_open(dvr, O_RDONLY)) < 0 )
    {
        msg_Err( p_access, "DVROpen: opening device failed: %s",
                 vlc_strerror_c(errno) );
        return VLC_EGENERIC;
    }

    if( fcntl( p_sys->i_handle, F_SETFL, O_NONBLOCK ) == -1 )
    {
        msg_Warn( p_access, "DVROpen: couldn't set non-blocking mode: %s",
                  vlc_strerror_c(errno) );
    }

    return VLC_SUCCESS;
}