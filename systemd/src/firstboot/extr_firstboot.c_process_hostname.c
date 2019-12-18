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
 int WRITE_STRING_FILE_CREATE ; 
 int WRITE_STRING_FILE_MKDIR_0755 ; 
 int WRITE_STRING_FILE_SYNC ; 
 int /*<<< orphan*/  arg_hostname ; 
 int /*<<< orphan*/  arg_root ; 
 scalar_t__ isempty (int /*<<< orphan*/ ) ; 
 scalar_t__ laccess (char const*,int /*<<< orphan*/ ) ; 
 int log_error_errno (int,char*,char const*) ; 
 int /*<<< orphan*/  log_info (char*,char const*) ; 
 char* prefix_roota (int /*<<< orphan*/ ,char*) ; 
 int prompt_hostname () ; 
 int write_string_file (char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int process_hostname(void) {
        const char *etc_hostname;
        int r;

        etc_hostname = prefix_roota(arg_root, "/etc/hostname");
        if (laccess(etc_hostname, F_OK) >= 0)
                return 0;

        r = prompt_hostname();
        if (r < 0)
                return r;

        if (isempty(arg_hostname))
                return 0;

        r = write_string_file(etc_hostname, arg_hostname,
                              WRITE_STRING_FILE_CREATE | WRITE_STRING_FILE_SYNC | WRITE_STRING_FILE_MKDIR_0755);
        if (r < 0)
                return log_error_errno(r, "Failed to write %s: %m", etc_hostname);

        log_info("%s written.", etc_hostname);
        return 0;
}