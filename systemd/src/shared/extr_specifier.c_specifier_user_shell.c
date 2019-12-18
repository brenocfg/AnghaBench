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
 int get_shell (char**) ; 

int specifier_user_shell(char specifier, const void *data, const void *userdata, char **ret) {

        /* On PID 1 (which runs as root) this will not result in NSS,
         * which is good. See above */

        return get_shell(ret);
}