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
 char* ansi_highlight_yellow () ; 
 char* ansi_normal () ; 
 int /*<<< orphan*/  assert (char const**) ; 
 scalar_t__ streq_ptr (char const*,char*) ; 

__attribute__((used)) static void operational_state_to_color(const char *name, const char *state, const char **on, const char **off) {
        assert(on);
        assert(off);

        if (STRPTR_IN_SET(state, "routable", "enslaved") ||
            (streq_ptr(name, "lo") && streq_ptr(state, "carrier"))) {
                *on = ansi_highlight_green();
                *off = ansi_normal();
        } else if (streq_ptr(state, "degraded")) {
                *on = ansi_highlight_yellow();
                *off = ansi_normal();
        } else
                *on = *off = "";
}