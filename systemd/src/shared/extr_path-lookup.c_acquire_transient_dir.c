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
typedef  scalar_t__ UnitFileScope ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 char** IN_SET (scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ UNIT_FILE_GLOBAL ; 
 scalar_t__ UNIT_FILE_SYSTEM ; 
 int /*<<< orphan*/  UNIT_FILE_USER ; 
 int /*<<< orphan*/  assert (char**) ; 
 char* path_join (char const*,char*) ; 
 char* strdup (char*) ; 
 int xdg_user_runtime_dir (char**,char*) ; 

__attribute__((used)) static int acquire_transient_dir(
                UnitFileScope scope,
                const char *tempdir,
                char **ret) {

        char *transient;

        assert(ret);
        assert(IN_SET(scope, UNIT_FILE_SYSTEM, UNIT_FILE_USER, UNIT_FILE_GLOBAL));

        if (scope == UNIT_FILE_GLOBAL)
                return -EOPNOTSUPP;

        if (tempdir)
                transient = path_join(tempdir, "transient");
        else if (scope == UNIT_FILE_SYSTEM)
                transient = strdup("/run/systemd/transient");
        else
                return xdg_user_runtime_dir(ret, "/systemd/transient");

        if (!transient)
                return -ENOMEM;
        *ret = transient;
        return 0;
}