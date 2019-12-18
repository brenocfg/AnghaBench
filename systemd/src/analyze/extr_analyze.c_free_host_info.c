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
struct host_info {struct host_info* architecture; struct host_info* virtualization; struct host_info* os_pretty_name; struct host_info* kernel_version; struct host_info* kernel_release; struct host_info* kernel_name; struct host_info* hostname; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct host_info*) ; 

__attribute__((used)) static void free_host_info(struct host_info *hi) {
        if (!hi)
                return;

        free(hi->hostname);
        free(hi->kernel_name);
        free(hi->kernel_release);
        free(hi->kernel_version);
        free(hi->os_pretty_name);
        free(hi->virtualization);
        free(hi->architecture);
        free(hi);
}