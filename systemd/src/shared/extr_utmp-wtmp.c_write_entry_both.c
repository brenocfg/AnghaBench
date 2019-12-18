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
 int write_utmp_wtmp (struct utmpx const*,struct utmpx const*) ; 

__attribute__((used)) static int write_entry_both(const struct utmpx *store) {
        return write_utmp_wtmp(store, store);
}