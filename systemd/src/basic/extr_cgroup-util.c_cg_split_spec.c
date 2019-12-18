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
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  cg_controller_is_valid (char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ isempty (char const*) ; 
 int /*<<< orphan*/  path_is_absolute (char*) ; 
 int /*<<< orphan*/  path_is_normalized (char const*) ; 
 char* path_simplify (char*,int) ; 
 char* strchr (char const*,char) ; 
 char* strdup (char const*) ; 
 char* strndup (char const*,int) ; 

int cg_split_spec(const char *spec, char **controller, char **path) {
        char *t = NULL, *u = NULL;
        const char *e;

        assert(spec);

        if (*spec == '/') {
                if (!path_is_normalized(spec))
                        return -EINVAL;

                if (path) {
                        t = strdup(spec);
                        if (!t)
                                return -ENOMEM;

                        *path = path_simplify(t, false);
                }

                if (controller)
                        *controller = NULL;

                return 0;
        }

        e = strchr(spec, ':');
        if (!e) {
                if (!cg_controller_is_valid(spec))
                        return -EINVAL;

                if (controller) {
                        t = strdup(spec);
                        if (!t)
                                return -ENOMEM;

                        *controller = t;
                }

                if (path)
                        *path = NULL;

                return 0;
        }

        t = strndup(spec, e-spec);
        if (!t)
                return -ENOMEM;
        if (!cg_controller_is_valid(t)) {
                free(t);
                return -EINVAL;
        }

        if (isempty(e+1))
                u = NULL;
        else {
                u = strdup(e+1);
                if (!u) {
                        free(t);
                        return -ENOMEM;
                }

                if (!path_is_normalized(u) ||
                    !path_is_absolute(u)) {
                        free(t);
                        free(u);
                        return -EINVAL;
                }

                path_simplify(u, false);
        }

        if (controller)
                *controller = t;
        else
                free(t);

        if (path)
                *path = u;
        else
                free(u);

        return 0;
}