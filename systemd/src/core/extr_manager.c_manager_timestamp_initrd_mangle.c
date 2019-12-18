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
typedef  scalar_t__ ManagerTimestamp ;

/* Variables and functions */
 scalar_t__ MANAGER_TIMESTAMP_INITRD_SECURITY_START ; 
 scalar_t__ MANAGER_TIMESTAMP_SECURITY_START ; 
 scalar_t__ MANAGER_TIMESTAMP_UNITS_LOAD_FINISH ; 
 scalar_t__ in_initrd () ; 

ManagerTimestamp manager_timestamp_initrd_mangle(ManagerTimestamp s) {
        if (in_initrd() &&
            s >= MANAGER_TIMESTAMP_SECURITY_START &&
            s <= MANAGER_TIMESTAMP_UNITS_LOAD_FINISH)
                return s - MANAGER_TIMESTAMP_SECURITY_START + MANAGER_TIMESTAMP_INITRD_SECURITY_START;
        return s;
}