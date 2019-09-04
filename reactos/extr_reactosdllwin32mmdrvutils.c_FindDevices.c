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
typedef  scalar_t__ SHORT ;
typedef  scalar_t__ MMRESULT ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  AddDeviceToList (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AuxDevice ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  DeviceList ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 scalar_t__ MMSYSERR_NOERROR ; 
 int /*<<< orphan*/  MidiInDevice ; 
 int /*<<< orphan*/  MidiOutDevice ; 
 scalar_t__ OpenDevice (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SOUND_MAX_DEVICE_NAME ; 
 int /*<<< orphan*/  WaveInDevice ; 
 int /*<<< orphan*/  WaveOutDevice ; 
 int /*<<< orphan*/  wsprintf (int /*<<< orphan*/ *,char*,scalar_t__) ; 

MMRESULT FindDevices()
{
//    DWORD Index;
//    HKEY DriverKey;

    DPRINT("Finding devices\n");
    
//    DriverKey = OpenParametersKey();
//  see drvutil.c of MS DDK for how this SHOULD be done...

  
    SHORT i;
    HANDLE h;
    WCHAR DeviceName[SOUND_MAX_DEVICE_NAME]; 

    for (i=0; OpenDevice(WaveOutDevice, i, &h, GENERIC_READ) == MMSYSERR_NOERROR; i++) 
    { 
        wsprintf(DeviceName, L"WaveOut%d\0", i);
        CloseHandle(h);
        AddDeviceToList(&DeviceList, WaveOutDevice, 0, DeviceName);
    }

    for (i=0; OpenDevice(WaveInDevice, i, &h, GENERIC_READ) == MMSYSERR_NOERROR; i++) 
    { 
        wsprintf(DeviceName, L"WaveIn%d\0", i);
        CloseHandle(h);
        AddDeviceToList(&DeviceList, WaveInDevice, 0, DeviceName);
    }

    for (i=0; OpenDevice(MidiOutDevice, i, &h, GENERIC_READ) == MMSYSERR_NOERROR; i++) 
    { 
        wsprintf(DeviceName, L"MidiOut%d\0", i);
        CloseHandle(h);
        AddDeviceToList(&DeviceList, MidiOutDevice, 0, DeviceName);
    }

    for (i=0; OpenDevice(MidiInDevice, i, &h, GENERIC_READ) == MMSYSERR_NOERROR; i++) 
    { 
        wsprintf(DeviceName, L"MidiIn%d\0", i);
        CloseHandle(h);
        AddDeviceToList(&DeviceList, MidiInDevice, 0, DeviceName);
    }

    for (i=0; OpenDevice(AuxDevice, i, &h, GENERIC_READ) == MMSYSERR_NOERROR; i++) 
    { 
        wsprintf(DeviceName, L"Aux%d\0", i);
        CloseHandle(h);
        AddDeviceToList(&DeviceList, AuxDevice, 0, DeviceName);
    }


    // MIDI Out 0: MPU-401 UART
    // AddDeviceToList(&DeviceList, MidiOutDevice, 0, L"MidiOut0");
    // Wave Out 0: Sound Blaster 16 (ok?)
    // AddDeviceToList(&DeviceList, WaveOutDevice, 0, L"WaveOut0");

    return MMSYSERR_NOERROR; // ok?
}