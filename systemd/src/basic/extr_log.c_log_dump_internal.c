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
typedef  size_t LogRealm ;

/* Variables and functions */
 int ERRNO_VALUE (int) ; 
 scalar_t__ LOG_PRI (int) ; 
 size_t LOG_REALM_REMOVE_LEVEL (int) ; 
 int /*<<< orphan*/  PROTECT_ERRNO ; 
 scalar_t__ _likely_ (int) ; 
 int log_dispatch_internal (int,int,char const*,int,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 scalar_t__* log_max_level ; 

int log_dump_internal(
                int level,
                int error,
                const char *file,
                int line,
                const char *func,
                char *buffer) {

        LogRealm realm = LOG_REALM_REMOVE_LEVEL(level);
        PROTECT_ERRNO;

        /* This modifies the buffer... */

        if (_likely_(LOG_PRI(level) > log_max_level[realm]))
                return -ERRNO_VALUE(error);

        return log_dispatch_internal(level, error, file, line, func, NULL, NULL, NULL, NULL, buffer);
}