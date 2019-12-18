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
 int /*<<< orphan*/  PROTECT_ERRNO ; 
 int /*<<< orphan*/  mac_selinux_use () ; 
 int /*<<< orphan*/  setsockcreatecon_raw (int /*<<< orphan*/ *) ; 

void mac_selinux_create_socket_clear(void) {

#if HAVE_SELINUX
        PROTECT_ERRNO;

        if (!mac_selinux_use())
                return;

        setsockcreatecon_raw(NULL);
#endif
}