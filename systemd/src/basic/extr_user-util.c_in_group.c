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
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int get_group_creds (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int in_gid (int /*<<< orphan*/ ) ; 

int in_group(const char *name) {
        int r;
        gid_t gid;

        r = get_group_creds(&name, &gid, 0);
        if (r < 0)
                return r;

        return in_gid(gid);
}