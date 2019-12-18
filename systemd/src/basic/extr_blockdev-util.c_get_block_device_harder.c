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
typedef  char const dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (char const*) ; 
 int block_get_originating (char const,char const*) ; 
 int get_block_device (char const*,char const*) ; 
 int /*<<< orphan*/  log_debug_errno (int,char*,char const*) ; 

int get_block_device_harder(const char *path, dev_t *ret) {
        int r;

        assert(path);
        assert(ret);

        /* Gets the backing block device for a file system, and handles LUKS encrypted file systems, looking for its
         * immediate parent, if there is one. */

        r = get_block_device(path, ret);
        if (r <= 0)
                return r;

        r = block_get_originating(*ret, ret);
        if (r < 0)
                log_debug_errno(r, "Failed to chase block device '%s', ignoring: %m", path);

        return 1;
}