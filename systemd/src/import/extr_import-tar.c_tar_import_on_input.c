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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  sd_event_source ;
typedef  int /*<<< orphan*/  TarImport ;

/* Variables and functions */
 int tar_import_process (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tar_import_on_input(sd_event_source *s, int fd, uint32_t revents, void *userdata) {
        TarImport *i = userdata;

        return tar_import_process(i);
}