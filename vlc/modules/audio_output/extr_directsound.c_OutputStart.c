#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  audio_sample_format_t ;
struct TYPE_12__ {int /*<<< orphan*/  flush; int /*<<< orphan*/  pause; int /*<<< orphan*/  play; int /*<<< orphan*/  time_get; TYPE_3__* sys; } ;
typedef  TYPE_2__ audio_output_t ;
struct TYPE_11__ {int /*<<< orphan*/  mute; int /*<<< orphan*/  volume; } ;
struct TYPE_13__ {TYPE_1__ volume; int /*<<< orphan*/  s; } ;
typedef  TYPE_3__ aout_sys_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ InitDirectSound (TYPE_2__*) ; 
 int /*<<< orphan*/  MuteSet (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OutputFlush ; 
 int /*<<< orphan*/  OutputPause ; 
 int /*<<< orphan*/  OutputPlay ; 
 int /*<<< orphan*/  OutputTimeGet ; 
 int /*<<< orphan*/  Start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_2__*) ; 
 int /*<<< orphan*/  VolumeSet (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*) ; 

__attribute__((used)) static int OutputStart( audio_output_t *p_aout,
                        audio_sample_format_t *restrict fmt )
{
    msg_Dbg( p_aout, "Opening DirectSound Audio Output" );

    /* Initialise DirectSound */
    if( InitDirectSound( p_aout ) )
    {
        msg_Err( p_aout, "cannot initialize DirectSound" );
        return -1;
    }

    aout_sys_t *sys = p_aout->sys;
    HRESULT hr = Start( VLC_OBJECT(p_aout), &sys->s, fmt );
    if( FAILED(hr) )
        return -1;

    /* Force volume update */
    VolumeSet( p_aout, sys->volume.volume );
    MuteSet( p_aout, sys->volume.mute );

    /* then launch the notification thread */
    p_aout->time_get = OutputTimeGet;
    p_aout->play = OutputPlay;
    p_aout->pause = OutputPause;
    p_aout->flush = OutputFlush;

    return 0;
}