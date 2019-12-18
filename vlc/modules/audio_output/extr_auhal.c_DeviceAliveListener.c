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
typedef  int /*<<< orphan*/  const* UInt32 ;
typedef  int OSStatus ;
typedef  int /*<<< orphan*/  AudioObjectPropertyAddress ;
typedef  int /*<<< orphan*/  const* AudioObjectID ;

/* Variables and functions */
 int /*<<< orphan*/  AOUT_RESTART_OUTPUT ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  aout_RestartRequest (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*) ; 
 int noErr ; 

__attribute__((used)) static OSStatus
DeviceAliveListener(AudioObjectID inObjectID,  UInt32 inNumberAddresses,
                    const AudioObjectPropertyAddress inAddresses[],
                    void *inClientData)
{
    VLC_UNUSED(inObjectID);
    VLC_UNUSED(inNumberAddresses);
    VLC_UNUSED(inAddresses);

    audio_output_t *p_aout = (audio_output_t *)inClientData;
    if (!p_aout)
        return -1;

    msg_Warn(p_aout, "audio device died, resetting aout");
    aout_RestartRequest(p_aout, AOUT_RESTART_OUTPUT);

    return noErr;
}