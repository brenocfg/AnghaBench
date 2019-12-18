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
typedef  scalar_t__ EmergencyAction ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ EMERGENCY_ACTION_NONE ; 
 int EOPNOTSUPP ; 
 scalar_t__ _EMERGENCY_ACTION_FIRST_USER_ACTION ; 
 scalar_t__ emergency_action_from_string (char const*) ; 

int parse_emergency_action(
                const char *value,
                bool system,
                EmergencyAction *ret) {

        EmergencyAction x;

        x = emergency_action_from_string(value);
        if (x < 0)
                return -EINVAL;

        if (!system && x != EMERGENCY_ACTION_NONE && x < _EMERGENCY_ACTION_FIRST_USER_ACTION)
                return -EOPNOTSUPP;

        *ret = x;
        return 0;
}