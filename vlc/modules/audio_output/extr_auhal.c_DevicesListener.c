#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ audio_output_t ;
struct TYPE_7__ {int /*<<< orphan*/  selected_device_lock; int /*<<< orphan*/  device_list_lock; int /*<<< orphan*/  device_list; int /*<<< orphan*/  i_selected_dev; } ;
typedef  TYPE_2__ aout_sys_t ;
typedef  int /*<<< orphan*/  const* UInt32 ;
typedef  int OSStatus ;
typedef  int /*<<< orphan*/  CFRange ;
typedef  int /*<<< orphan*/  CFNumberRef ;
typedef  int /*<<< orphan*/  AudioObjectPropertyAddress ;
typedef  int /*<<< orphan*/  const* AudioObjectID ;

/* Variables and functions */
 int /*<<< orphan*/  AOUT_RESTART_OUTPUT ; 
 int /*<<< orphan*/  CFArrayContainsValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFArrayGetCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFNumberCreate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CFRangeMake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RebuildDeviceList (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  aout_RestartRequest (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kCFAllocatorDefault ; 
 int /*<<< orphan*/  kCFNumberSInt32Type ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*) ; 
 int noErr ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static OSStatus
DevicesListener(AudioObjectID inObjectID, UInt32 inNumberAddresses,
                const AudioObjectPropertyAddress inAddresses[],
                void *inClientData)
{
    VLC_UNUSED(inObjectID);
    VLC_UNUSED(inNumberAddresses);
    VLC_UNUSED(inAddresses);

    audio_output_t *p_aout = (audio_output_t *)inClientData;
    if (!p_aout)
        return -1;
    aout_sys_t *p_sys = p_aout->sys;

    msg_Dbg(p_aout, "audio device configuration changed, resetting cache");
    RebuildDeviceList(p_aout, NULL);

    vlc_mutex_lock(&p_sys->selected_device_lock);
    vlc_mutex_lock(&p_sys->device_list_lock);
    CFNumberRef selectedDevice =
        CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt32Type,
                       &p_sys->i_selected_dev);
    CFRange range = CFRangeMake(0, CFArrayGetCount(p_sys->device_list));
    if (!CFArrayContainsValue(p_sys->device_list, range, selectedDevice))
        aout_RestartRequest(p_aout, AOUT_RESTART_OUTPUT);
    CFRelease(selectedDevice);
    vlc_mutex_unlock(&p_sys->device_list_lock);
    vlc_mutex_unlock(&p_sys->selected_device_lock);

    return noErr;
}