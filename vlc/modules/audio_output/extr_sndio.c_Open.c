#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_2__ {int /*<<< orphan*/  stop; int /*<<< orphan*/  start; int /*<<< orphan*/ * sys; } ;
typedef  TYPE_1__ audio_output_t ;
typedef  int /*<<< orphan*/  aout_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  Start ; 
 int /*<<< orphan*/  Stop ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/ * malloc (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Open (vlc_object_t *obj)
{
    audio_output_t *aout = (audio_output_t *)obj;
    aout_sys_t *sys = malloc (sizeof (*sys));
    if (unlikely(sys == NULL))
        return VLC_ENOMEM;

    aout->sys = sys;
    aout->start = Start;
    aout->stop = Stop;
    /* FIXME: set volume/mute here */
    return VLC_SUCCESS;
}