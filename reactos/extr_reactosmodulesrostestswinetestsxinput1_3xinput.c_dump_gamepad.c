#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  sThumbRY; int /*<<< orphan*/  sThumbRX; int /*<<< orphan*/  sThumbLY; int /*<<< orphan*/  sThumbLX; int /*<<< orphan*/  bRightTrigger; int /*<<< orphan*/  bLeftTrigger; int /*<<< orphan*/  wButtons; } ;
typedef  TYPE_1__ XINPUT_GAMEPAD ;

/* Variables and functions */
 int /*<<< orphan*/  trace (char*,...) ; 

__attribute__((used)) static void dump_gamepad(XINPUT_GAMEPAD *data)
{
    trace("-- Gamepad Variables --\n");
    trace("Gamepad.wButtons: %#x\n", data->wButtons);
    trace("Gamepad.bLeftTrigger: %d\n", data->bLeftTrigger);
    trace("Gamepad.bRightTrigger: %d\n", data->bRightTrigger);
    trace("Gamepad.sThumbLX: %d\n", data->sThumbLX);
    trace("Gamepad.sThumbLY: %d\n", data->sThumbLY);
    trace("Gamepad.sThumbRX: %d\n", data->sThumbRX);
    trace("Gamepad.sThumbRY: %d\n\n", data->sThumbRY);
}