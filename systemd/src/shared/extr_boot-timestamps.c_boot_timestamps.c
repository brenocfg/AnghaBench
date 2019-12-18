#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ usec_t ;
struct TYPE_7__ {scalar_t__ monotonic; scalar_t__ realtime; } ;
typedef  TYPE_1__ dual_timestamp ;

/* Variables and functions */
 int acpi_get_boot_usec (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  dual_timestamp_get (TYPE_1__*) ; 
 int efi_loader_get_boot_usec (scalar_t__*,scalar_t__*) ; 

int boot_timestamps(const dual_timestamp *n, dual_timestamp *firmware, dual_timestamp *loader) {
        usec_t x = 0, y = 0, a;
        int r;
        dual_timestamp _n;

        assert(firmware);
        assert(loader);

        if (!n) {
                dual_timestamp_get(&_n);
                n = &_n;
        }

        r = acpi_get_boot_usec(&x, &y);
        if (r < 0) {
                r = efi_loader_get_boot_usec(&x, &y);
                if (r < 0)
                        return r;
        }

        /* Let's convert this to timestamps where the firmware
         * began/loader began working. To make this more confusing:
         * since usec_t is unsigned and the kernel's monotonic clock
         * begins at kernel initialization we'll actually initialize
         * the monotonic timestamps here as negative of the actual
         * value. */

        firmware->monotonic = y;
        loader->monotonic = y - x;

        a = n->monotonic + firmware->monotonic;
        firmware->realtime = n->realtime > a ? n->realtime - a : 0;

        a = n->monotonic + loader->monotonic;
        loader->realtime = n->realtime > a ? n->realtime - a : 0;

        return 0;
}