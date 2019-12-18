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
typedef  int /*<<< orphan*/  sd_id128_t ;

/* Variables and functions */
 int sd_id128_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sd_id128_from_string (char const*,int /*<<< orphan*/ *) ; 
 int sd_id128_get_machine (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dirname_is_machine_id(const char *fn) {
        sd_id128_t id, machine;
        int r;

        r = sd_id128_get_machine(&machine);
        if (r < 0)
                return r;

        r = sd_id128_from_string(fn, &id);
        if (r < 0)
                return r;

        return sd_id128_equal(id, machine);
}