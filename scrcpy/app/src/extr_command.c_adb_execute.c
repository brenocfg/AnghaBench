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
typedef  enum process_result { ____Placeholder_process_result } process_result ;

/* Variables and functions */
 int /*<<< orphan*/  PROCESS_NONE ; 
 int PROCESS_SUCCESS ; 
 int cmd_execute (char const*,char const**,int /*<<< orphan*/ *) ; 
 char* get_adb_command () ; 
 int /*<<< orphan*/  memcpy (char const**,char const* const*,size_t) ; 
 int /*<<< orphan*/  show_adb_err_msg (int,char const**) ; 

process_t
adb_execute(const char *serial, const char *const adb_cmd[], size_t len) {
    const char *cmd[len + 4];
    int i;
    process_t process;
    cmd[0] = get_adb_command();
    if (serial) {
        cmd[1] = "-s";
        cmd[2] = serial;
        i = 3;
    } else {
        i = 1;
    }

    memcpy(&cmd[i], adb_cmd, len * sizeof(const char *));
    cmd[len + i] = NULL;
    enum process_result r = cmd_execute(cmd[0], cmd, &process);
    if (r != PROCESS_SUCCESS) {
        show_adb_err_msg(r, cmd);
        return PROCESS_NONE;
    }
    return process;
}