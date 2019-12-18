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
 int simple_varlink_call (char*,char*) ; 

__attribute__((used)) static int flush_to_var(void) {
        return simple_varlink_call("--flush", "io.systemd.Journal.FlushToVar");
}