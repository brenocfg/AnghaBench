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
typedef  int /*<<< orphan*/  state ;
struct TYPE_8__ {int /*<<< orphan*/  sThumbRY; int /*<<< orphan*/  sThumbRX; int /*<<< orphan*/  sThumbLY; int /*<<< orphan*/  sThumbLX; int /*<<< orphan*/  bRightTrigger; int /*<<< orphan*/  bLeftTrigger; int /*<<< orphan*/  wButtons; } ;
struct TYPE_7__ {int dwPacketNumber; TYPE_2__ Gamepad; } ;
typedef  TYPE_1__ XINPUT_STATE ;
typedef  TYPE_2__ XINPUT_GAMEPAD ;
typedef  int DWORD ;

/* Variables and functions */
 int ERROR_BAD_ARGUMENTS ; 
 int ERROR_DEVICE_NOT_CONNECTED ; 
 int ERROR_SUCCESS ; 
 int GetTickCount () ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int XUSER_MAX_COUNT ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  dump_gamepad (TYPE_2__*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pXInputGetState (int,TYPE_1__*) ; 
 int pXInputGetStateEx (int,TYPE_1__*) ; 
 int /*<<< orphan*/  skip (char*,int) ; 
 int /*<<< orphan*/  trace (char*,...) ; 
 scalar_t__ winetest_interactive ; 

__attribute__((used)) static void test_get_state(void)
{
    XINPUT_STATE state;
    DWORD controllerNum, i, result, good = XUSER_MAX_COUNT;

    for (i = 0; i < (pXInputGetStateEx ? 2 : 1); i++)
    {
        for (controllerNum = 0; controllerNum < XUSER_MAX_COUNT; controllerNum++)
        {
            ZeroMemory(&state, sizeof(state));

            if (i == 0)
                result = pXInputGetState(controllerNum, &state);
            else
                result = pXInputGetStateEx(controllerNum, &state);
            ok(result == ERROR_SUCCESS || result == ERROR_DEVICE_NOT_CONNECTED,
               "%s failed with (%d)\n", i == 0 ? "XInputGetState" : "XInputGetStateEx", result);

            if (ERROR_DEVICE_NOT_CONNECTED == result)
            {
                skip("Controller %d is not connected\n", controllerNum);
                continue;
            }

            trace("-- Results for controller %d --\n", controllerNum);
            if (i == 0)
            {
                good = controllerNum;
                trace("XInputGetState: %d\n", result);
            }
            else
                trace("XInputGetStateEx: %d\n", result);
            trace("State->dwPacketNumber: %d\n", state.dwPacketNumber);
            dump_gamepad(&state.Gamepad);
        }
    }

    result = pXInputGetState(XUSER_MAX_COUNT, &state);
    ok(result == ERROR_BAD_ARGUMENTS, "XInputGetState returned (%d)\n", result);

    result = pXInputGetState(XUSER_MAX_COUNT+1, &state);
    ok(result == ERROR_BAD_ARGUMENTS, "XInputGetState returned (%d)\n", result);
    if (pXInputGetStateEx)
    {
        result = pXInputGetStateEx(XUSER_MAX_COUNT, &state);
        ok(result == ERROR_BAD_ARGUMENTS, "XInputGetState returned (%d)\n", result);

        result = pXInputGetStateEx(XUSER_MAX_COUNT+1, &state);
        ok(result == ERROR_BAD_ARGUMENTS, "XInputGetState returned (%d)\n", result);
    }

    if (winetest_interactive && good < XUSER_MAX_COUNT)
    {
        DWORD now = GetTickCount(), packet = 0;
        XINPUT_GAMEPAD *game = &state.Gamepad;

        trace("You have 20 seconds to test the joystick freely\n");
        do
        {
            Sleep(100);
            pXInputGetState(good, &state);
            if (state.dwPacketNumber == packet)
                continue;

            packet = state.dwPacketNumber;
            trace("Buttons 0x%04X Triggers %3d/%3d LT %6d/%6d RT %6d/%6d\n",
                  game->wButtons, game->bLeftTrigger, game->bRightTrigger,
                  game->sThumbLX, game->sThumbLY, game->sThumbRX, game->sThumbRY);
        }
        while(GetTickCount() - now < 20000);
        trace("Test over...\n");
    }
}