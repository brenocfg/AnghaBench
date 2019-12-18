#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ code; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ sd_bus_error_map ;

/* Variables and functions */
 TYPE_1__* ALIGN_TO_PTR (TYPE_1__ const*,int) ; 
 scalar_t__ BUS_ERROR_MAP_END_MARKER ; 
 TYPE_1__ const* __start_SYSTEMD_BUS_ERROR_MAP ; 
 TYPE_1__ const* __stop_SYSTEMD_BUS_ERROR_MAP ; 
 int /*<<< orphan*/  errno_to_name (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* strna (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dump_mapping_table(void) {
        const sd_bus_error_map *m;

        printf("----- errno mappings ------\n");
        m = ALIGN_TO_PTR(__start_SYSTEMD_BUS_ERROR_MAP, sizeof(void*));
        while (m < __stop_SYSTEMD_BUS_ERROR_MAP) {

                if (m->code == BUS_ERROR_MAP_END_MARKER) {
                        m = ALIGN_TO_PTR(m + 1, sizeof(void*));
                        continue;
                }

                printf("%s -> %i/%s\n", strna(m->name), m->code, strna(errno_to_name(m->code)));
                m++;
        }
        printf("---------------------------\n");
}