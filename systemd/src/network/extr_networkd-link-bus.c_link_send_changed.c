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
typedef  int /*<<< orphan*/  Link ;

/* Variables and functions */
 int link_send_changed_strv (int /*<<< orphan*/ *,char**) ; 
 char** strv_from_stdarg_alloca (char const*) ; 

int link_send_changed(Link *link, const char *property, ...) {
        char **properties;

        properties = strv_from_stdarg_alloca(property);

        return link_send_changed_strv(link, properties);
}