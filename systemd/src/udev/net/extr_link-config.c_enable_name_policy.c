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
 scalar_t__ proc_cmdline_get_bool (char*,int*) ; 

__attribute__((used)) static bool enable_name_policy(void) {
        bool b;

        return proc_cmdline_get_bool("net.ifnames", &b) <= 0 || b;
}