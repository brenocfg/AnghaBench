#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_4__ {int /*<<< orphan*/  CommitWaveBuffer; int /*<<< orphan*/  Close; int /*<<< orphan*/  Open; int /*<<< orphan*/  SetWaveFormat; int /*<<< orphan*/  QueryWaveFormatSupport; int /*<<< orphan*/  GetCapabilities; } ;
typedef  scalar_t__ PWSTR ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/ * PSOUND_DEVICE ;
typedef  int /*<<< orphan*/  MMRESULT ;
typedef  TYPE_1__ MMFUNCTION_TABLE ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 scalar_t__ AllocateWideString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CloseNt4SoundDevice ; 
 int /*<<< orphan*/  CopyWideString (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetSoundBlasterDeviceCapabilities ; 
 int /*<<< orphan*/  ListSoundDevice (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  MMSUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OpenNt4SoundDevice ; 
 int /*<<< orphan*/  QueryNt4WaveDeviceFormatSupport ; 
 int /*<<< orphan*/  SND_TRACE (char*,scalar_t__) ; 
 int /*<<< orphan*/  SetNt4WaveDeviceFormat ; 
 int /*<<< orphan*/  SetSoundDeviceFunctionTable (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WriteFileEx_Committer ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  wcslen (scalar_t__) ; 

BOOLEAN FoundDevice(
    UCHAR DeviceType,
    PWSTR DevicePath)
{
    MMRESULT Result;
    PSOUND_DEVICE SoundDevice = NULL;
    MMFUNCTION_TABLE FuncTable;
    PWSTR PathCopy;

    SND_TRACE(L"(Callback) Found device: %wS\n", DevicePath);

    PathCopy = AllocateWideString(wcslen(DevicePath));

    if ( ! PathCopy )
        return FALSE;

    CopyWideString(PathCopy, DevicePath);

    Result = ListSoundDevice(DeviceType, (PVOID) PathCopy, &SoundDevice);

    if ( ! MMSUCCESS(Result) )
        return FALSE;

    /* Set up our function table */
    ZeroMemory(&FuncTable, sizeof(MMFUNCTION_TABLE));
    FuncTable.GetCapabilities = GetSoundBlasterDeviceCapabilities;
    FuncTable.QueryWaveFormatSupport = QueryNt4WaveDeviceFormatSupport;
    FuncTable.SetWaveFormat = SetNt4WaveDeviceFormat;
    FuncTable.Open = OpenNt4SoundDevice;
    FuncTable.Close = CloseNt4SoundDevice;
    FuncTable.CommitWaveBuffer = WriteFileEx_Committer;
    //FuncTable.SubmitWaveHeaderToDevice = SubmitWaveHeaderToDevice;

    SetSoundDeviceFunctionTable(SoundDevice, &FuncTable);

    return TRUE;
}