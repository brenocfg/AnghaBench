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
typedef  int Boolean ;
typedef  int /*<<< orphan*/  AudioObjectPropertyAddress ;
typedef  int /*<<< orphan*/  AudioObjectID ;

/* Variables and functions */
 scalar_t__ AudioObjectIsPropertySettable (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int*) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*,int) ; 
 scalar_t__ noErr ; 

__attribute__((used)) static bool
AoIsPropertySettable(audio_output_t *p_aout, AudioObjectID id,
                     const AudioObjectPropertyAddress *p_address)
{
    Boolean b_settable;
    OSStatus err = AudioObjectIsPropertySettable(id, p_address, &b_settable);
    if (err != noErr)
    {
        msg_Warn(p_aout, "AudioObjectIsPropertySettable failed, device id: %i, "
                 "prop: [%4.4s], OSStatus: %d", id, (const char *)&p_address[0],
                 (int)err);
        return false;
    }
    return b_settable;
}