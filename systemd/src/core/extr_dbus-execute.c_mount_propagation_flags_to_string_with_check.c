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
 int /*<<< orphan*/  IN_SET (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MS_PRIVATE ; 
 int /*<<< orphan*/  MS_SHARED ; 
 int /*<<< orphan*/  MS_SLAVE ; 
 char const* mount_propagation_flags_to_string (unsigned long) ; 

__attribute__((used)) static const char* mount_propagation_flags_to_string_with_check(unsigned long n) {
        if (!IN_SET(n, 0, MS_SHARED, MS_PRIVATE, MS_SLAVE))
                return NULL;

        return mount_propagation_flags_to_string(n);
}