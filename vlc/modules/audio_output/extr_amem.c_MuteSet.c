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
struct TYPE_4__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ audio_output_t ;
struct TYPE_5__ {int mute; int (* set_volume ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  lock; int /*<<< orphan*/  volume; int /*<<< orphan*/  opaque; scalar_t__ ready; } ;
typedef  TYPE_2__ aout_sys_t ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int MuteSet (audio_output_t *aout, bool mute)
{
    aout_sys_t *sys = aout->sys;
    int val;

    sys->mute = mute;

    vlc_mutex_lock(&sys->lock);
    if (sys->ready)
        val = sys->set_volume(sys->opaque, sys->volume, mute);
    else
        val = 0; /* sys->opaque is not yet defined... */
    vlc_mutex_unlock(&sys->lock);

    return val ? -1 : 0;
}