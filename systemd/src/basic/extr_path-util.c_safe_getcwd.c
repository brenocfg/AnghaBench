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
 int ENOMEDIUM ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_current_dir_name () ; 
 int negative_errno () ; 

int safe_getcwd(char **ret) {
        char *cwd;

        cwd = get_current_dir_name();
        if (!cwd)
                return negative_errno();

        /* Let's make sure the directory is really absolute, to protect us from the logic behind
         * CVE-2018-1000001 */
        if (cwd[0] != '/') {
                free(cwd);
                return -ENOMEDIUM;
        }

        *ret = cwd;
        return 0;
}