#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  maxmemory_policy; } ;

/* Variables and functions */
 char const* configEnumGetNameOrUnknown (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maxmemory_policy_enum ; 
 TYPE_1__ server ; 

const char *evictPolicyToString(void) {
    return configEnumGetNameOrUnknown(maxmemory_policy_enum,server.maxmemory_policy);
}