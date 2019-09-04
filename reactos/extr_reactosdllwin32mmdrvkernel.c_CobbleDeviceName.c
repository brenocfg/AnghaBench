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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  PWCHAR ;
typedef  int /*<<< orphan*/  MMRESULT ;
typedef  int DeviceType ;

/* Variables and functions */
 int /*<<< orphan*/  AUX_DEVICE_NAME ; 
#define  AuxDevice 132 
 int MAX_DEVICE_NAME_LENGTH ; 
 int /*<<< orphan*/  MIDI_IN_DEVICE_NAME ; 
 int /*<<< orphan*/  MIDI_OUT_DEVICE_NAME ; 
 int /*<<< orphan*/  MMSYSERR_BADDEVICEID ; 
 int /*<<< orphan*/  MMSYSERR_NOERROR ; 
#define  MidiInDevice 131 
#define  MidiOutDevice 130 
 int /*<<< orphan*/  WAVE_IN_DEVICE_NAME ; 
 int /*<<< orphan*/  WAVE_OUT_DEVICE_NAME ; 
#define  WaveInDevice 129 
#define  WaveOutDevice 128 
 int strlen (char*) ; 
 int /*<<< orphan*/  wsprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,...) ; 

MMRESULT
CobbleDeviceName(
    DeviceType device_type,
    UINT device_id,
    PWCHAR out_device_name)
{
    WCHAR base_device_name[MAX_DEVICE_NAME_LENGTH];

    /* Work out the base name from the device type */

    switch ( device_type )
    {
        case WaveOutDevice :
            wsprintf(base_device_name, L"%ls", WAVE_OUT_DEVICE_NAME);
            break;

        case WaveInDevice :
            wsprintf(base_device_name, L"%ls", WAVE_IN_DEVICE_NAME);
            break;

        case MidiOutDevice :
            wsprintf(base_device_name, L"%ls", MIDI_OUT_DEVICE_NAME);
            break;

        case MidiInDevice :
            wsprintf(base_device_name, L"%ls", MIDI_IN_DEVICE_NAME);
            break;

        case AuxDevice :
            wsprintf(base_device_name, L"%ls", AUX_DEVICE_NAME);
            break;

        default :
            return MMSYSERR_BADDEVICEID;
    };

    /* Now append the device number, removing the leading \Device */

    wsprintf(out_device_name,
             L"\\\\.%ls%d",
             base_device_name + strlen("\\Device"),
             device_id);

    return MMSYSERR_NOERROR;
}