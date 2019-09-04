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
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOGE (char*,...) ; 
 long strtol (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
parse_max_size(char *optarg, uint16_t *max_size) {
    char *endptr;
    if (*optarg == '\0') {
        LOGE("Max size parameter is empty");
        return false;
    }
    long value = strtol(optarg, &endptr, 0);
    if (*endptr != '\0') {
        LOGE("Invalid max size: %s", optarg);
        return false;
    }
    if (value & ~0xffff) {
        LOGE("Max size must be between 0 and 65535: %ld", value);
        return false;
    }

    *max_size = (uint16_t) value;
    return true;
}