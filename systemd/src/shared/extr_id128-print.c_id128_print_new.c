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
 int id128_pretty_print (int /*<<< orphan*/ ,int) ; 
 int log_error_errno (int,char*) ; 
 int sd_id128_randomize (int /*<<< orphan*/ *) ; 

int id128_print_new(bool pretty) {
        sd_id128_t id;
        int r;

        r = sd_id128_randomize(&id);
        if (r < 0)
                return log_error_errno(r, "Failed to generate ID: %m");

        return id128_pretty_print(id, pretty);
}