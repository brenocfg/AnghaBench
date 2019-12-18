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
typedef  int /*<<< orphan*/  audio_output_t ;
typedef  scalar_t__ OSStatus ;
typedef  int /*<<< orphan*/  AudioUnit ;

/* Variables and functions */
 scalar_t__ AudioUnitUninitialize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ca_LogWarn (char*) ; 
 int /*<<< orphan*/  ca_Uninitialize (int /*<<< orphan*/ *) ; 
 scalar_t__ noErr ; 

void
au_Uninitialize(audio_output_t *p_aout, AudioUnit au)
{
    OSStatus err = AudioUnitUninitialize(au);
    if (err != noErr)
        ca_LogWarn("AudioUnitUninitialize failed");

    ca_Uninitialize(p_aout);
}