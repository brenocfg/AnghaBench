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

/* Variables and functions */
 int /*<<< orphan*/  DUMP_STRING_TABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeviceAction ; 
 int /*<<< orphan*/  _DEVICE_ACTION_MAX ; 
 int /*<<< orphan*/  device_action ; 

void dump_device_action_table(void) {
        DUMP_STRING_TABLE(device_action, DeviceAction, _DEVICE_ACTION_MAX);
}