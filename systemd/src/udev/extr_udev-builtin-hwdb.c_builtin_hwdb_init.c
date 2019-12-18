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
 scalar_t__ hwdb ; 
 int sd_hwdb_new (scalar_t__*) ; 

__attribute__((used)) static int builtin_hwdb_init(void) {
        int r;

        if (hwdb)
                return 0;

        r = sd_hwdb_new(&hwdb);
        if (r < 0)
                return r;

        return 0;
}