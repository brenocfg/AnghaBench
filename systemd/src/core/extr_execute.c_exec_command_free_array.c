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
typedef  int /*<<< orphan*/  ExecCommand ;

/* Variables and functions */
 int /*<<< orphan*/ * exec_command_free_list (int /*<<< orphan*/ *) ; 

void exec_command_free_array(ExecCommand **c, size_t n) {
        size_t i;

        for (i = 0; i < n; i++)
                c[i] = exec_command_free_list(c[i]);
}