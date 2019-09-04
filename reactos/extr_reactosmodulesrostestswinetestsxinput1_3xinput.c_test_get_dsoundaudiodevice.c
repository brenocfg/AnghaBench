#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; int member_6; int member_7; } ;
struct TYPE_8__ {int member_0; int member_1; int member_2; TYPE_1__ member_3; } ;
typedef  TYPE_2__ GUID ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_BAD_ARGUMENTS ; 
 scalar_t__ ERROR_DEVICE_NOT_CONNECTED ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  IsEqualGUID (TYPE_2__*,TYPE_2__*) ; 
 scalar_t__ XUSER_MAX_COUNT ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pXInputGetDSoundAudioDeviceGuids (scalar_t__,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  skip (char*,scalar_t__) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_get_dsoundaudiodevice(void)
{
    DWORD controllerNum;
    DWORD result;
    GUID soundRender, soundCapture;
    GUID testGuid = {0xFFFFFFFF, 0xFFFF, 0xFFFF, {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}};
    GUID emptyGuid = {0x0, 0x0, 0x0, {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0}};

    for(controllerNum = 0; controllerNum < XUSER_MAX_COUNT; controllerNum++)
    {
        soundRender = soundCapture = testGuid;
        result = pXInputGetDSoundAudioDeviceGuids(controllerNum, &soundRender, &soundCapture);
        ok(result == ERROR_SUCCESS || result == ERROR_DEVICE_NOT_CONNECTED, "XInputGetDSoundAudioDeviceGuids failed with (%d)\n", result);

        if (ERROR_DEVICE_NOT_CONNECTED == result)
        {
            skip("Controller %d is not connected\n", controllerNum);
            continue;
        }

        if (!IsEqualGUID(&soundRender, &emptyGuid))
            ok(!IsEqualGUID(&soundRender, &testGuid), "Broken GUID returned for sound render device\n");
        else
            trace("Headset phone not attached\n");

        if (!IsEqualGUID(&soundCapture, &emptyGuid))
            ok(!IsEqualGUID(&soundCapture, &testGuid), "Broken GUID returned for sound capture device\n");
        else
            trace("Headset microphone not attached\n");
    }

    result = pXInputGetDSoundAudioDeviceGuids(XUSER_MAX_COUNT+1, &soundRender, &soundCapture);
    ok(result == ERROR_BAD_ARGUMENTS, "XInputGetDSoundAudioDeviceGuids returned (%d)\n", result);
}