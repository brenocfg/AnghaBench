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
struct dirent {char* d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  streq (char*,char*) ; 

__attribute__((used)) static int usbffs_select_ep(const struct dirent *d) {
        return d->d_name[0] != '.' && !streq(d->d_name, "ep0");
}