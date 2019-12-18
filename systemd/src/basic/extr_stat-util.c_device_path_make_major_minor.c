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
 int ENOMEM ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ asprintf (char**,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  major (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  minor (int /*<<< orphan*/ ) ; 

int device_path_make_major_minor(mode_t mode, dev_t devno, char **ret) {
        const char *t;

        /* Generates the /dev/{char|block}/MAJOR:MINOR path for a dev_t */

        if (S_ISCHR(mode))
                t = "char";
        else if (S_ISBLK(mode))
                t = "block";
        else
                return -ENODEV;

        if (asprintf(ret, "/dev/%s/%u:%u", t, major(devno), minor(devno)) < 0)
                return -ENOMEM;

        return 0;
}