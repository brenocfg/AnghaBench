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
struct TYPE_5__ {scalar_t__ p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_6__ {int b_stereo; int i_sample_rate; int i_max_frame_size; int /*<<< orphan*/  psz_device; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 int AFMT_S16_LE ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  SNDCTL_DSP_SETFMT ; 
 int /*<<< orphan*/  SNDCTL_DSP_SPEED ; 
 int /*<<< orphan*/  SNDCTL_DSP_STEREO ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_close (int) ; 
 int vlc_open (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vlc_strerror_c (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int OpenAudioDevOss( demux_t *p_demux )
{
    demux_sys_t *p_sys = (demux_sys_t *)p_demux->p_sys;
    int i_fd;
    int i_format;

    i_fd = vlc_open( p_sys->psz_device, O_RDONLY | O_NONBLOCK );

    if( i_fd < 0 )
    {
        msg_Err( p_demux, "cannot open OSS audio device (%s)",
                 vlc_strerror_c(errno) );
        goto adev_fail;
    }

    i_format = AFMT_S16_LE;
    if( ioctl( i_fd, SNDCTL_DSP_SETFMT, &i_format ) < 0
        || i_format != AFMT_S16_LE )
    {
        msg_Err( p_demux,
                 "cannot set audio format (16b little endian) (%s)",
                 vlc_strerror_c(errno) );
        goto adev_fail;
    }

    if( ioctl( i_fd, SNDCTL_DSP_STEREO, &p_sys->b_stereo ) < 0 )
    {
        msg_Err( p_demux, "cannot set audio channels count (%s)",
                 vlc_strerror_c(errno) );
        goto adev_fail;
    }

    if( ioctl( i_fd, SNDCTL_DSP_SPEED, &p_sys->i_sample_rate ) < 0 )
    {
        msg_Err( p_demux, "cannot set audio sample rate (%s)",
                 vlc_strerror_c(errno) );
        goto adev_fail;
    }

    p_sys->i_max_frame_size = 6 * 1024;

    return i_fd;

 adev_fail:

    if( i_fd >= 0 )
        vlc_close( i_fd );
    return -1;
}