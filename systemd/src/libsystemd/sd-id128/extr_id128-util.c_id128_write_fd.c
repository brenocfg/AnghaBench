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
typedef  scalar_t__ Id128Format ;

/* Variables and functions */
 scalar_t__ ID128_UUID ; 
 scalar_t__ _ID128_FORMAT_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 
 scalar_t__ fsync (int) ; 
 int fsync_directory_of_file (int) ; 
 int /*<<< orphan*/  id128_to_uuid_string (int /*<<< orphan*/ ,char*) ; 
 int loop_write (int,char*,size_t,int) ; 
 int /*<<< orphan*/  sd_id128_to_string (int /*<<< orphan*/ ,char*) ; 

int id128_write_fd(int fd, Id128Format f, sd_id128_t id, bool do_sync) {
        char buffer[36 + 2];
        size_t sz;
        int r;

        assert(fd >= 0);
        assert(f < _ID128_FORMAT_MAX);

        if (f != ID128_UUID) {
                sd_id128_to_string(id, buffer);
                buffer[32] = '\n';
                sz = 33;
        } else {
                id128_to_uuid_string(id, buffer);
                buffer[36] = '\n';
                sz = 37;
        }

        r = loop_write(fd, buffer, sz, false);
        if (r < 0)
                return r;

        if (do_sync) {
                if (fsync(fd) < 0)
                        return -errno;

                r = fsync_directory_of_file(fd);
                if (r < 0)
                        return r;
        }

        return 0;
}