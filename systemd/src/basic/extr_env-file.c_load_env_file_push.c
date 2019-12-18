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
 int check_utf8ness_and_warn (char const*,unsigned int,char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strjoin (char const*,char*,char*) ; 
 int strv_env_replace (char***,char*) ; 

__attribute__((used)) static int load_env_file_push(
                const char *filename, unsigned line,
                const char *key, char *value,
                void *userdata,
                int *n_pushed) {
        char ***m = userdata;
        char *p;
        int r;

        r = check_utf8ness_and_warn(filename, line, key, value);
        if (r < 0)
                return r;

        p = strjoin(key, "=", value);
        if (!p)
                return -ENOMEM;

        r = strv_env_replace(m, p);
        if (r < 0) {
                free(p);
                return r;
        }

        if (n_pushed)
                (*n_pushed)++;

        free(value);
        return 0;
}