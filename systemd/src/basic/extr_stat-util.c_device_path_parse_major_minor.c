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
typedef  int /*<<< orphan*/  mode_t ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  S_IFBLK ; 
 int /*<<< orphan*/  S_IFCHR ; 
 int /*<<< orphan*/  makedev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int parse_dev (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ path_equal (char const*,char*) ; 
 char* path_startswith (char const*,char*) ; 

int device_path_parse_major_minor(const char *path, mode_t *ret_mode, dev_t *ret_devno) {
        mode_t mode;
        dev_t devno;
        int r;

        /* Tries to extract the major/minor directly from the device path if we can. Handles /dev/block/ and /dev/char/
         * paths, as well out synthetic inaccessible device nodes. Never goes to disk. Returns -ENODEV if the device
         * path cannot be parsed like this.  */

        if (path_equal(path, "/run/systemd/inaccessible/chr")) {
                mode = S_IFCHR;
                devno = makedev(0, 0);
        } else if (path_equal(path, "/run/systemd/inaccessible/blk")) {
                mode = S_IFBLK;
                devno = makedev(0, 0);
        } else {
                const char *w;

                w = path_startswith(path, "/dev/block/");
                if (w)
                        mode = S_IFBLK;
                else {
                        w = path_startswith(path, "/dev/char/");
                        if (!w)
                                return -ENODEV;

                        mode = S_IFCHR;
                }

                r = parse_dev(w, &devno);
                if (r < 0)
                        return r;
        }

        if (ret_mode)
                *ret_mode = mode;
        if (ret_devno)
                *ret_devno = devno;

        return 0;
}