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
struct utmpx {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int write_entry_utmp (struct utmpx const*) ; 
 int write_entry_wtmp (struct utmpx const*) ; 

__attribute__((used)) static int write_utmp_wtmp(const struct utmpx *store_utmp, const struct utmpx *store_wtmp) {
        int r, s;

        r = write_entry_utmp(store_utmp);
        s = write_entry_wtmp(store_wtmp);

        if (r >= 0)
                r = s;

        /* If utmp/wtmp have been disabled, that's a good thing, hence
         * ignore the errors */
        if (r == -ENOENT)
                r = 0;

        return r;
}