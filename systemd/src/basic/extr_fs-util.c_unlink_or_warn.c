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
 scalar_t__ ENOENT ; 
 scalar_t__ EROFS ; 
 int /*<<< orphan*/  F_OK ; 
 scalar_t__ access (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int log_error_errno (scalar_t__,char*,char const*) ; 
 scalar_t__ unlink (char const*) ; 

int unlink_or_warn(const char *filename) {
        if (unlink(filename) < 0 && errno != ENOENT)
                /* If the file doesn't exist and the fs simply was read-only (in which
                 * case unlink() returns EROFS even if the file doesn't exist), don't
                 * complain */
                if (errno != EROFS || access(filename, F_OK) >= 0)
                        return log_error_errno(errno, "Failed to remove \"%s\": %m", filename);

        return 0;
}