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
 int cached_colors_enabled ; 
 scalar_t__ cached_columns ; 
 scalar_t__ cached_lines ; 
 int cached_on_tty ; 
 int cached_underline_enabled ; 

void reset_terminal_feature_caches(void) {
        cached_columns = 0;
        cached_lines = 0;

        cached_colors_enabled = -1;
        cached_underline_enabled = -1;
        cached_on_tty = -1;
}