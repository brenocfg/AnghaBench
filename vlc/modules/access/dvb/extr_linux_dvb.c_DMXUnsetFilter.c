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

/* Variables and functions */
 int /*<<< orphan*/  DMX_STOP ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_close (int) ; 
 int /*<<< orphan*/  vlc_strerror_c (int /*<<< orphan*/ ) ; 

int DMXUnsetFilter( vlc_object_t *p_access, int i_fd )
{
    if( ioctl( i_fd, DMX_STOP ) < 0 )
    {
        msg_Err( p_access, "stopping demux failed: %s",
                 vlc_strerror_c(errno) );
        return VLC_EGENERIC;
    }

    msg_Dbg( p_access, "DMXUnsetFilter: closing demux %d", i_fd );
    vlc_close( i_fd );
    return VLC_SUCCESS;
}