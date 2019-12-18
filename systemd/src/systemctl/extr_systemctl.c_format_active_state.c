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
 scalar_t__ STRPTR_IN_SET (char const*,char*,char*) ; 
 char* ansi_highlight_green () ; 
 char* ansi_highlight_red () ; 
 char* ansi_normal () ; 
 scalar_t__ streq_ptr (char const*,char*) ; 

__attribute__((used)) static void format_active_state(const char *active_state, const char **active_on, const char **active_off) {
        if (streq_ptr(active_state, "failed")) {
                *active_on = ansi_highlight_red();
                *active_off = ansi_normal();
        } else if (STRPTR_IN_SET(active_state, "active", "reloading")) {
                *active_on = ansi_highlight_green();
                *active_off = ansi_normal();
        } else
                *active_on = *active_off = "";
}