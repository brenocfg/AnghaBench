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
typedef  int /*<<< orphan*/  sd_bus_error ;

/* Variables and functions */
 int /*<<< orphan*/  SD_BUS_ERROR_ACCESS_DENIED ; 
 int /*<<< orphan*/  SD_BUS_ERROR_DISCONNECTED ; 
 int /*<<< orphan*/  SD_BUS_ERROR_NAME_HAS_NO_OWNER ; 
 int /*<<< orphan*/  SD_BUS_ERROR_NO_REPLY ; 
 int /*<<< orphan*/  SD_BUS_ERROR_SERVICE_UNKNOWN ; 
 int /*<<< orphan*/  SD_BUS_ERROR_TIMEOUT ; 
 scalar_t__ sd_bus_error_has_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool bus_error_shall_fallback(sd_bus_error *e) {
        return sd_bus_error_has_name(e, SD_BUS_ERROR_SERVICE_UNKNOWN) ||
               sd_bus_error_has_name(e, SD_BUS_ERROR_NAME_HAS_NO_OWNER) ||
               sd_bus_error_has_name(e, SD_BUS_ERROR_NO_REPLY) ||
               sd_bus_error_has_name(e, SD_BUS_ERROR_ACCESS_DENIED) ||
               sd_bus_error_has_name(e, SD_BUS_ERROR_DISCONNECTED) ||
               sd_bus_error_has_name(e, SD_BUS_ERROR_TIMEOUT);
}