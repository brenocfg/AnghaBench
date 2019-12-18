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
 int STR_IN_SET (char const*,char*,char*,char*) ; 

__attribute__((used)) static bool service_family_is_valid(const char *s) {
        return STR_IN_SET(s, "tcp", "udp", "sctp");
}