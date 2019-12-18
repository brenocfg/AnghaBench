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
 int /*<<< orphan*/  F_OK ; 
 int SD_ID128_STRING_MAX ; 
 int WRITE_STRING_FILE_CREATE ; 
 int WRITE_STRING_FILE_MKDIR_0755 ; 
 int WRITE_STRING_FILE_SYNC ; 
 int /*<<< orphan*/  arg_machine_id ; 
 int /*<<< orphan*/  arg_root ; 
 scalar_t__ laccess (char const*,int /*<<< orphan*/ ) ; 
 int log_error_errno (int,char*) ; 
 int /*<<< orphan*/  log_info (char*,char const*) ; 
 char* prefix_roota (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ sd_id128_is_null (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_id128_to_string (int /*<<< orphan*/ ,char*) ; 
 int write_string_file (char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int process_machine_id(void) {
        const char *etc_machine_id;
        char id[SD_ID128_STRING_MAX];
        int r;

        etc_machine_id = prefix_roota(arg_root, "/etc/machine-id");
        if (laccess(etc_machine_id, F_OK) >= 0)
                return 0;

        if (sd_id128_is_null(arg_machine_id))
                return 0;

        r = write_string_file(etc_machine_id, sd_id128_to_string(arg_machine_id, id),
                              WRITE_STRING_FILE_CREATE | WRITE_STRING_FILE_SYNC | WRITE_STRING_FILE_MKDIR_0755);
        if (r < 0)
                return log_error_errno(r, "Failed to write machine id: %m");

        log_info("%s written.", etc_machine_id);
        return 0;
}