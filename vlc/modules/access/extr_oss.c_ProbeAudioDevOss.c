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
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  SNDCTL_DSP_GETCAPS ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,char const*,...) ; 
 int /*<<< orphan*/  vlc_close (int) ; 
 int vlc_open (char const*,int) ; 
 int /*<<< orphan*/  vlc_strerror_c (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ProbeAudioDevOss( demux_t *p_demux, const char *psz_device )
{
    int i_caps;
    int i_fd = vlc_open( psz_device, O_RDONLY | O_NONBLOCK );

    if( i_fd < 0 )
    {
        msg_Err( p_demux, "cannot open device %s for OSS audio (%s)",
                 psz_device, vlc_strerror_c(errno) );
        goto open_failed;
    }

    /* this will fail if the device is video */
    if( ioctl( i_fd, SNDCTL_DSP_GETCAPS, &i_caps ) < 0 )
    {
        msg_Err( p_demux, "cannot get audio caps (%s)",
                 vlc_strerror_c(errno) );
        goto open_failed;
    }

    if( i_fd >= 0 )
        vlc_close( i_fd );

    return true;

open_failed:
    if( i_fd >= 0 )
        vlc_close( i_fd );
    return false;
}