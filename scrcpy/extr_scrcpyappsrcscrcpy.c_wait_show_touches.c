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
typedef  int /*<<< orphan*/  process_t ;

/* Variables and functions */
 int /*<<< orphan*/  process_check_success (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
wait_show_touches(process_t process) {
    // reap the process, ignore the result
    process_check_success(process, "show_touches");
}