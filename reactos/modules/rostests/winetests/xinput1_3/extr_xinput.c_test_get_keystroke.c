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
typedef  int /*<<< orphan*/  XINPUT_KEYSTROKE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_BAD_ARGUMENTS ; 
 scalar_t__ ERROR_DEVICE_NOT_CONNECTED ; 
 scalar_t__ ERROR_EMPTY ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  XINPUT_FLAG_GAMEPAD ; 
 scalar_t__ XUSER_MAX_COUNT ; 
 int /*<<< orphan*/  ZeroMemory (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pXInputGetKeystroke (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip (char*,scalar_t__) ; 

__attribute__((used)) static void test_get_keystroke(void)
{
    XINPUT_KEYSTROKE keystroke;
    DWORD controllerNum;
    DWORD result;

    for(controllerNum = 0; controllerNum < XUSER_MAX_COUNT; controllerNum++)
    {
        ZeroMemory(&keystroke, sizeof(XINPUT_KEYSTROKE));

        result = pXInputGetKeystroke(controllerNum, XINPUT_FLAG_GAMEPAD, &keystroke);
        ok(result == ERROR_EMPTY || result == ERROR_SUCCESS || result == ERROR_DEVICE_NOT_CONNECTED,
           "XInputGetKeystroke failed with (%d)\n", result);

        if (ERROR_DEVICE_NOT_CONNECTED == result)
        {
            skip("Controller %d is not connected\n", controllerNum);
        }
    }

    ZeroMemory(&keystroke, sizeof(XINPUT_KEYSTROKE));
    result = pXInputGetKeystroke(XUSER_MAX_COUNT+1, XINPUT_FLAG_GAMEPAD, &keystroke);
    ok(result == ERROR_BAD_ARGUMENTS, "XInputGetKeystroke returned (%d)\n", result);
}