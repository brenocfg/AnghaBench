#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int UnitFileFlags ;
struct TYPE_3__ {scalar_t__ type; char* path; } ;
typedef  TYPE_1__ UnitFileChange ;

/* Variables and functions */
 char** STRV_MAKE (char const*) ; 
 int UNIT_FILE_DRY_RUN ; 
 int UNIT_FILE_RUNTIME ; 
 int /*<<< orphan*/  UNIT_FILE_SYSTEM ; 
 scalar_t__ UNIT_FILE_UNLINK ; 
 scalar_t__ arg_runtime ; 
 int log_error_errno (int,char*,char const*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int unit_file_disable (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,char**,TYPE_1__**,size_t*) ; 

__attribute__((used)) static int show_installation_targets_client_side(const char *name) {
        UnitFileChange *changes = NULL;
        size_t n_changes = 0, i;
        UnitFileFlags flags;
        char **p;
        int r;

        p = STRV_MAKE(name);
        flags = UNIT_FILE_DRY_RUN |
                (arg_runtime ? UNIT_FILE_RUNTIME : 0);

        r = unit_file_disable(UNIT_FILE_SYSTEM, flags, NULL, p, &changes, &n_changes);
        if (r < 0)
                return log_error_errno(r, "Failed to get file links for %s: %m", name);

        for (i = 0; i < n_changes; i++)
                if (changes[i].type == UNIT_FILE_UNLINK)
                        printf("  %s\n", changes[i].path);

        return 0;
}