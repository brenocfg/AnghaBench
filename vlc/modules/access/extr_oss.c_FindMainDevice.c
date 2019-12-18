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
struct TYPE_7__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_8__ {scalar_t__ i_fd; int /*<<< orphan*/  psz_device; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 scalar_t__ OpenAudioDev (TYPE_1__*) ; 
 scalar_t__ ProbeAudioDevOss (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int FindMainDevice( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;

    msg_Dbg( p_demux, "opening device '%s'", p_sys->psz_device );
    if( ProbeAudioDevOss( p_demux, p_sys->psz_device ) )
    {
        msg_Dbg( p_demux, "'%s' is an audio device", p_sys->psz_device );
        p_sys->i_fd = OpenAudioDev( p_demux );
    }

    if( p_sys->i_fd < 0 )
        return VLC_EGENERIC;
    return VLC_SUCCESS;
}