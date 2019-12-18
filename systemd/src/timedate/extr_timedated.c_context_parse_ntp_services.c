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
 int context_parse_ntp_services_from_disk (int /*<<< orphan*/ *) ; 
 int context_parse_ntp_services_from_environment (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int context_parse_ntp_services(Context *c) {
        int r;

        r = context_parse_ntp_services_from_environment(c);
        if (r != 0)
                return r;

        return context_parse_ntp_services_from_disk(c);
}