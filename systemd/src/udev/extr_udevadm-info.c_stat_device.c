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
struct stat {int /*<<< orphan*/  st_dev; } ;

/* Variables and functions */
 int errno ; 
 int major (int /*<<< orphan*/ ) ; 
 int minor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ stat (char const*,struct stat*) ; 

__attribute__((used)) static int stat_device(const char *name, bool export, const char *prefix) {
        struct stat statbuf;

        if (stat(name, &statbuf) != 0)
                return -errno;

        if (export) {
                if (!prefix)
                        prefix = "INFO_";
                printf("%sMAJOR=%u\n"
                       "%sMINOR=%u\n",
                       prefix, major(statbuf.st_dev),
                       prefix, minor(statbuf.st_dev));
        } else
                printf("%u:%u\n", major(statbuf.st_dev), minor(statbuf.st_dev));
        return 0;
}