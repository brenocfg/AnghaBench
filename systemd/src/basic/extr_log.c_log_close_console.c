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
 int /*<<< orphan*/  console_fd ; 
 int /*<<< orphan*/  safe_close_above_stdio (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void log_close_console(void) {
        console_fd = safe_close_above_stdio(console_fd);
}