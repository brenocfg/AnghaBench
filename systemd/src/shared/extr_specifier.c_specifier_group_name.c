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
 int /*<<< orphan*/  getgid () ; 
 char* gid_to_name (int /*<<< orphan*/ ) ; 

int specifier_group_name(char specifier, const void *data, const void *userdata, char **ret) {
        char *t;

        t = gid_to_name(getgid());
        if (!t)
                return -ENOMEM;

        *ret = t;
        return 0;
}