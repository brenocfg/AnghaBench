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
typedef  enum process_result { ____Placeholder_process_result } process_result ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  LOGE (char*,...) ; 
#define  PROCESS_ERROR_GENERIC 130 
#define  PROCESS_ERROR_MISSING_BINARY 129 
#define  PROCESS_SUCCESS 128 
 int /*<<< orphan*/  argv_to_string (char const* const*,char*,int) ; 

__attribute__((used)) static void
show_adb_err_msg(enum process_result err, const char *const argv[]) {
    char buf[512];
    switch (err) {
        case PROCESS_ERROR_GENERIC:
            argv_to_string(argv, buf, sizeof(buf));
            LOGE("Failed to execute: %s", buf);
            break;
        case PROCESS_ERROR_MISSING_BINARY:
            argv_to_string(argv, buf, sizeof(buf));
            LOGE("Command not found: %s", buf);
            LOGE("(make 'adb' accessible from your PATH or define its full"
                 "path in the ADB environment variable)");
            break;
        case PROCESS_SUCCESS:
            // do nothing
            break;
    }
}