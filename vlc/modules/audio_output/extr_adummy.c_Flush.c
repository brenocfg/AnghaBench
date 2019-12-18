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
struct aout_sys {scalar_t__ length; int /*<<< orphan*/  first_play_date; } ;
struct TYPE_3__ {struct aout_sys* sys; } ;
typedef  TYPE_1__ audio_output_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_TICK_INVALID ; 

__attribute__((used)) static void Flush(audio_output_t *aout)
{
    struct aout_sys *sys = aout->sys;

    sys->first_play_date = VLC_TICK_INVALID;
    sys->length = 0;
}