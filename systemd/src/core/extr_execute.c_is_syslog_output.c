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
typedef  int /*<<< orphan*/  ExecOutput ;

/* Variables and functions */
 int /*<<< orphan*/  EXEC_OUTPUT_SYSLOG ; 
 int /*<<< orphan*/  EXEC_OUTPUT_SYSLOG_AND_CONSOLE ; 
 int IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_syslog_output(ExecOutput o) {
        return IN_SET(o,
                      EXEC_OUTPUT_SYSLOG,
                      EXEC_OUTPUT_SYSLOG_AND_CONSOLE);
}