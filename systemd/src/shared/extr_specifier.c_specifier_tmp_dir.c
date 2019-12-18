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
 int ENOMEM ; 
 char* strdup (char const*) ; 
 int tmp_dir (char const**) ; 

int specifier_tmp_dir(char specifier, const void *data, const void *userdata, char **ret) {
        const char *p;
        char *copy;
        int r;

        r = tmp_dir(&p);
        if (r < 0)
                return r;

        copy = strdup(p);
        if (!copy)
                return -ENOMEM;

        *ret = copy;
        return 0;
}