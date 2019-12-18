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
typedef  int /*<<< orphan*/  Context ;

/* Variables and functions */
 int EINVAL ; 
 int network_set_dns (int /*<<< orphan*/ *,char*,char const*) ; 
 scalar_t__ proc_cmdline_value_missing (char const*,char const*) ; 

__attribute__((used)) static int parse_cmdline_nameserver(Context *context, const char *key, const char *value) {
        if (proc_cmdline_value_missing(key, value))
                return -EINVAL;

        return network_set_dns(context, "", value);
}