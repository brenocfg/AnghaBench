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
 int /*<<< orphan*/  assert (char const*) ; 
 int safe_atoi (char const*,int*) ; 
 char* skip_dev_prefix (char const*) ; 
 int /*<<< orphan*/  startswith (char const*,char*) ; 

int vtnr_from_tty(const char *tty) {
        int i, r;

        assert(tty);

        tty = skip_dev_prefix(tty);

        if (!startswith(tty, "tty") )
                return -EINVAL;

        if (tty[3] < '0' || tty[3] > '9')
                return -EINVAL;

        r = safe_atoi(tty+3, &i);
        if (r < 0)
                return r;

        if (i < 0 || i > 63)
                return -EINVAL;

        return i;
}