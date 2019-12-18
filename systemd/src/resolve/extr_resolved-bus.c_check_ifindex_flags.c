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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  sd_bus_error ;

/* Variables and functions */
 int /*<<< orphan*/  SD_BUS_ERROR_INVALID_ARGS ; 
 int SD_RESOLVED_NO_CNAME ; 
 int SD_RESOLVED_PROTOCOLS_ALL ; 
 int /*<<< orphan*/  assert (int*) ; 
 int sd_bus_error_setf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int check_ifindex_flags(int ifindex, uint64_t *flags, uint64_t ok, sd_bus_error *error) {
        assert(flags);

        if (ifindex < 0)
                return sd_bus_error_setf(error, SD_BUS_ERROR_INVALID_ARGS, "Invalid interface index");

        if (*flags & ~(SD_RESOLVED_PROTOCOLS_ALL|SD_RESOLVED_NO_CNAME|ok))
                return sd_bus_error_setf(error, SD_BUS_ERROR_INVALID_ARGS, "Invalid flags parameter");

        if ((*flags & SD_RESOLVED_PROTOCOLS_ALL) == 0) /* If no protocol is enabled, enable all */
                *flags |= SD_RESOLVED_PROTOCOLS_ALL;

        return 0;
}