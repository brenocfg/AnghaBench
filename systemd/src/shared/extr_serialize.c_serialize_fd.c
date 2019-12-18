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
typedef  char const FILE ;
typedef  int /*<<< orphan*/  FDSet ;

/* Variables and functions */
 int /*<<< orphan*/  assert (char const*) ; 
 int fdset_put_dup (int /*<<< orphan*/ *,int) ; 
 int log_error_errno (int,char*) ; 
 int serialize_item_format (char const*,char const*,char*,int) ; 

int serialize_fd(FILE *f, FDSet *fds, const char *key, int fd) {
        int copy;

        assert(f);
        assert(key);

        if (fd < 0)
                return 0;

        copy = fdset_put_dup(fds, fd);
        if (copy < 0)
                return log_error_errno(copy, "Failed to add file descriptor to serialization set: %m");

        return serialize_item_format(f, key, "%i", copy);
}