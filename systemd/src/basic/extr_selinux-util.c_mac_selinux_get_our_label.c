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
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  assert (char**) ; 
 int errno ; 
 int getcon_raw (char**) ; 
 int /*<<< orphan*/  mac_selinux_use () ; 

int mac_selinux_get_our_label(char **label) {
        int r = -EOPNOTSUPP;

        assert(label);

#if HAVE_SELINUX
        if (!mac_selinux_use())
                return -EOPNOTSUPP;

        r = getcon_raw(label);
        if (r < 0)
                return -errno;
#endif

        return r;
}