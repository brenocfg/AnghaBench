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
typedef  int /*<<< orphan*/  ExecCommandFlags ;

/* Variables and functions */
 int /*<<< orphan*/  EXEC_COMMAND_AMBIENT_MAGIC ; 
 int /*<<< orphan*/  EXEC_COMMAND_FULLY_PRIVILEGED ; 
 int /*<<< orphan*/  EXEC_COMMAND_IGNORE_FAILURE ; 
 int /*<<< orphan*/  EXEC_COMMAND_NO_ENV_EXPAND ; 
 int /*<<< orphan*/  EXEC_COMMAND_NO_SETUID ; 
 scalar_t__ FLAGS_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strjoin (char*,char*,char*,char*,char*) ; 

__attribute__((used)) static char *exec_command_flags_to_exec_chars(ExecCommandFlags flags) {
        return strjoin(FLAGS_SET(flags, EXEC_COMMAND_IGNORE_FAILURE)   ? "-" : "",
                       FLAGS_SET(flags, EXEC_COMMAND_NO_ENV_EXPAND)    ? ":" : "",
                       FLAGS_SET(flags, EXEC_COMMAND_FULLY_PRIVILEGED) ? "+" : "",
                       FLAGS_SET(flags, EXEC_COMMAND_NO_SETUID)        ? "!" : "",
                       FLAGS_SET(flags, EXEC_COMMAND_AMBIENT_MAGIC)    ? "!!" : "");
}