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
typedef  int /*<<< orphan*/  AudioObjectPropertyAddress ;
typedef  int /*<<< orphan*/  AudioObjectID ;

/* Variables and functions */
 scalar_t__ AudioObjectSetPropertyData (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,void const*) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*,int) ; 
 scalar_t__ noErr ; 

__attribute__((used)) static int
AoSetProperty(audio_output_t *p_aout, AudioObjectID id,
              const AudioObjectPropertyAddress *p_address, size_t i_data,
              const void *p_data)
{
    OSStatus err =
        AudioObjectSetPropertyData(id, p_address, 0, NULL, i_data, p_data);

    if (err != noErr)
    {
        msg_Err(p_aout, "AudioObjectSetPropertyData failed, device id: %i, "
                 "prop: [%4.4s], OSStatus: %d", id, (const char *)&p_address[0],
                 (int)err);
        return VLC_EGENERIC;
    }
    return VLC_SUCCESS;
}