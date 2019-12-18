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
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_5__ {int /*<<< orphan*/  synthUnit; int /*<<< orphan*/  end_date; } ;
typedef  TYPE_2__ decoder_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  MusicDeviceMIDIEvent (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  date_Set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kMidiController_AllSoundOff ; 
 unsigned int kMidiMessage_ControlChange ; 

__attribute__((used)) static void Flush (decoder_t *p_dec)
{
    decoder_sys_t *p_sys = p_dec->p_sys;

    date_Set(&p_sys->end_date, VLC_TICK_INVALID);

    // Turn all sound on all channels off
    // else 'old' notes could still be playing
    for (unsigned channel = 0; channel < 16; channel++) {
        MusicDeviceMIDIEvent(p_sys->synthUnit, kMidiMessage_ControlChange | channel, kMidiController_AllSoundOff, 0, 0);
    }
}