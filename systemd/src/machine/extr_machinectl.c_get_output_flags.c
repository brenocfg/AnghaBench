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
typedef  int OutputFlags ;

/* Variables and functions */
 int OUTPUT_COLOR ; 
 int OUTPUT_FULL_WIDTH ; 
 int OUTPUT_SHOW_ALL ; 
 int OUTPUT_WARN_CUTOFF ; 
 int arg_all ; 
 scalar_t__ arg_full ; 
 int /*<<< orphan*/  arg_quiet ; 
 int colors_enabled () ; 
 int /*<<< orphan*/  on_tty () ; 
 scalar_t__ pager_have () ; 

__attribute__((used)) static OutputFlags get_output_flags(void) {
        return
                arg_all * OUTPUT_SHOW_ALL |
                (arg_full || !on_tty() || pager_have()) * OUTPUT_FULL_WIDTH |
                colors_enabled() * OUTPUT_COLOR |
                !arg_quiet * OUTPUT_WARN_CUTOFF;
}