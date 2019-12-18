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
typedef  int /*<<< orphan*/  uid_t ;

/* Variables and functions */
 int EINVAL ; 
 int parse_uid (char const*,int /*<<< orphan*/ *) ; 
 char* startswith (char const*,char*) ; 
 char* strchr (char const*,char) ; 
 char* strndupa (char const*,int) ; 

__attribute__((used)) static int uid_from_file_name(const char *filename, uid_t *uid) {
        const char *p, *e, *u;

        p = startswith(filename, "core.");
        if (!p)
                return -EINVAL;

        /* Skip the comm field */
        p = strchr(p, '.');
        if (!p)
                return -EINVAL;
        p++;

        /* Find end up UID */
        e = strchr(p, '.');
        if (!e)
                return -EINVAL;

        u = strndupa(p, e-p);
        return parse_uid(u, uid);
}