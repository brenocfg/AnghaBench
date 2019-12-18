#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
struct TYPE_5__ {scalar_t__ (* time_get ) (TYPE_1__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* drain ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ audio_output_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 scalar_t__ stub2 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_tick_sleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aout_Drain(audio_output_t *aout)
{
    if (aout->drain)
        aout->drain(aout);
    else
    {
        vlc_tick_t delay;
        if (aout->time_get(aout, &delay) == 0)
            vlc_tick_sleep(delay);
    }
}