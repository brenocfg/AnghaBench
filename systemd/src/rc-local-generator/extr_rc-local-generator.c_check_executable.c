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
 scalar_t__ EACCES ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  X_OK ; 
 scalar_t__ access (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (char const*) ; 
 scalar_t__ errno ; 
 int log_debug_errno (scalar_t__,char*,char const*) ; 
 int log_info_errno (scalar_t__,char*,char const*) ; 
 int log_warning_errno (scalar_t__,char*,char const*) ; 

__attribute__((used)) static int check_executable(const char *path) {
        assert(path);

        if (access(path, X_OK) < 0) {
                if (errno == ENOENT)
                        return log_debug_errno(errno, "%s does not exist, skipping.", path);
                if (errno == EACCES)
                        return log_info_errno(errno, "%s is not marked executable, skipping.", path);

                return log_warning_errno(errno, "Couldn't determine if %s exists and is executable, skipping: %m", path);
        }

        return 0;
}