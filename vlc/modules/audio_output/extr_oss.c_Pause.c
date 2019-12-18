#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
struct TYPE_4__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ audio_output_t ;
struct TYPE_5__ {int fd; } ;
typedef  TYPE_2__ aout_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  SNDCTL_DSP_SILENCE ; 
 int /*<<< orphan*/  SNDCTL_DSP_SKIP ; 
 int /*<<< orphan*/  ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Pause (audio_output_t *aout, bool pause, vlc_tick_t date)
{
    aout_sys_t *sys = aout->sys;
    int fd = sys->fd;

    (void) date;
    ioctl (fd, pause ? SNDCTL_DSP_SILENCE : SNDCTL_DSP_SKIP, NULL);
}