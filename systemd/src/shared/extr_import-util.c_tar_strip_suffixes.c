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
 int EINVAL ; 
 int ENOMEM ; 
 char* endswith (char const*,char*) ; 
 char* strchr (char const*,int /*<<< orphan*/ ) ; 
 char* strndup (char const*,int) ; 

int tar_strip_suffixes(const char *name, char **ret) {
        const char *e;
        char *s;

        e = endswith(name, ".tar");
        if (!e)
                e = endswith(name, ".tar.xz");
        if (!e)
                e = endswith(name, ".tar.gz");
        if (!e)
                e = endswith(name, ".tar.bz2");
        if (!e)
                e = endswith(name, ".tgz");
        if (!e)
                e = strchr(name, 0);

        if (e <= name)
                return -EINVAL;

        s = strndup(name, e - name);
        if (!s)
                return -ENOMEM;

        *ret = s;
        return 0;
}