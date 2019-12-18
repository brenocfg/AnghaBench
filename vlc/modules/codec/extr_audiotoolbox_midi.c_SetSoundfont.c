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
typedef  int /*<<< orphan*/  url ;
typedef  int /*<<< orphan*/  decoder_t ;
typedef  int /*<<< orphan*/  UInt8 ;
typedef  scalar_t__ OSStatus ;
typedef  int /*<<< orphan*/ * CFURLRef ;
typedef  int /*<<< orphan*/  AudioUnit ;

/* Variables and functions */
 scalar_t__ AudioUnitSetProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CFURLCreateFromFileSystemRepresentation (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  kAudioUnitScope_Global ; 
 int /*<<< orphan*/  kCFAllocatorDefault ; 
 int /*<<< orphan*/  kMusicDeviceProperty_SoundBankURL ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 scalar_t__ noErr ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int SetSoundfont(decoder_t *p_dec, AudioUnit synthUnit, const char *sfPath) {
    if (!sfPath) {
        msg_Dbg(p_dec, "using default soundfont");
        return VLC_SUCCESS;
    }

    msg_Dbg(p_dec, "using custom soundfont: '%s'", sfPath);
    CFURLRef url = CFURLCreateFromFileSystemRepresentation(kCFAllocatorDefault,
                                                           (const UInt8 *)sfPath,
                                                           strlen(sfPath), false);
    if (unlikely(url == NULL))
        return VLC_ENOMEM;

    OSStatus status = AudioUnitSetProperty(synthUnit,
                                           kMusicDeviceProperty_SoundBankURL,
                                           kAudioUnitScope_Global, 0,
                                           &url, sizeof(url));
    CFRelease(url);

    if (status != noErr) {
        msg_Err(p_dec, "failed setting custom SoundFont for MIDI synthesis (%i)", status);
        return VLC_EGENERIC;
    }
    return VLC_SUCCESS;
}