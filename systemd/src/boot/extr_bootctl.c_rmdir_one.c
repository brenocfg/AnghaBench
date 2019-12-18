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
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOTEMPTY ; 
 int IN_SET (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int errno ; 
 int /*<<< orphan*/  log_full_errno (int /*<<< orphan*/ ,int,char*,char const*) ; 
 int /*<<< orphan*/  log_info (char*,char const*) ; 
 char* prefix_roota (char const*,char const*) ; 
 scalar_t__ rmdir (char const*) ; 

__attribute__((used)) static int rmdir_one(const char *prefix, const char *suffix) {
        const char *p;

        p = prefix_roota(prefix, suffix);
        if (rmdir(p) < 0) {
                bool ignore = IN_SET(errno, ENOENT, ENOTEMPTY);

                log_full_errno(ignore ? LOG_DEBUG : LOG_ERR, errno,
                               "Failed to remove directory \"%s\": %m", p);
                if (!ignore)
                        return -errno;
        } else
                log_info("Removed \"%s\".", p);

        return 0;
}