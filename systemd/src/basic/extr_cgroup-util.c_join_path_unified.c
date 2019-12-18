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
 int ENOMEM ; 
 int /*<<< orphan*/  assert (char**) ; 
 scalar_t__ isempty (char const*) ; 
 char* path_join (char*,char const*,...) ; 
 char* strdup (char*) ; 

__attribute__((used)) static int join_path_unified(const char *path, const char *suffix, char **fs) {
        char *t;

        assert(fs);

        if (isempty(path) && isempty(suffix))
                t = strdup("/sys/fs/cgroup");
        else if (isempty(path))
                t = path_join("/sys/fs/cgroup", suffix);
        else if (isempty(suffix))
                t = path_join("/sys/fs/cgroup", path);
        else
                t = path_join("/sys/fs/cgroup", path, suffix);
        if (!t)
                return -ENOMEM;

        *fs = t;
        return 0;
}