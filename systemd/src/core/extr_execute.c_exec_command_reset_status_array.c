#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  exec_status; } ;
typedef  TYPE_1__ ExecCommand ;

/* Variables and functions */
 int /*<<< orphan*/  exec_status_reset (int /*<<< orphan*/ *) ; 

void exec_command_reset_status_array(ExecCommand *c, size_t n) {
        size_t i;

        for (i = 0; i < n; i++)
                exec_status_reset(&c[i].exec_status);
}