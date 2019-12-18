#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t written_uncompressed; int /*<<< orphan*/  tar_fd; } ;
typedef  TYPE_1__ TarImport ;

/* Variables and functions */
 int loop_write (int /*<<< orphan*/ ,void const*,size_t,int) ; 

__attribute__((used)) static int tar_import_write(const void *p, size_t sz, void *userdata) {
        TarImport *i = userdata;
        int r;

        r = loop_write(i->tar_fd, p, sz, false);
        if (r < 0)
                return r;

        i->written_uncompressed += sz;

        return 0;
}