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
 int /*<<< orphan*/  LOG_NOTICE ; 
 int /*<<< orphan*/  free_and_replace (char*,char*) ; 
 int log_oom () ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int /*<<< orphan*/ ,char*,char const*,char*,char*) ; 
 char* path_join (char*,char const*) ; 
 char* path_startswith (char*,char*) ; 

__attribute__((used)) static int patch_var_run(
                const char *unit,
                const char *filename,
                unsigned line,
                const char *lvalue,
                char **path) {

        const char *e;
        char *z;

        e = path_startswith(*path, "/var/run/");
        if (!e)
                return 0;

        z = path_join("/run/", e);
        if (!z)
                return log_oom();

        log_syntax(unit, LOG_NOTICE, filename, line, 0,
                   "%s= references a path below legacy directory /var/run/, updating %s → %s; "
                   "please update the unit file accordingly.", lvalue, *path, z);

        free_and_replace(*path, z);

        return 1;
}