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
 int ENOENT ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int errno ; 
 int /*<<< orphan*/  log_full_errno (int /*<<< orphan*/ ,int,char*,char const*) ; 
 int /*<<< orphan*/  log_info (char*,char const*) ; 
 char* prefix_roota (char const*,char const*) ; 
 scalar_t__ unlink (char const*) ; 

__attribute__((used)) static int remove_file(const char *root, const char *file) {
        const char *p;

        assert(root);
        assert(file);

        p = prefix_roota(root, file);
        if (unlink(p) < 0) {
                log_full_errno(errno == ENOENT ? LOG_DEBUG : LOG_ERR, errno,
                               "Failed to unlink file \"%s\": %m", p);

                return errno == ENOENT ? 0 : -errno;
        }

        log_info("Removed \"%s\".", p);
        return 1;
}