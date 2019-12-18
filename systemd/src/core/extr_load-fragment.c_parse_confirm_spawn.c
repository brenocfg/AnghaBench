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
 scalar_t__ is_path (char const*) ; 
 int parse_boolean (char const*) ; 
 char* path_join (char*,char const*) ; 
 char* strdup (char const*) ; 

int parse_confirm_spawn(const char *value, char **console) {
        char *s;
        int r;

        r = value ? parse_boolean(value) : 1;
        if (r == 0) {
                *console = NULL;
                return 0;
        } else if (r > 0) /* on with default tty */
                s = strdup("/dev/console");
        else if (is_path(value)) /* on with fully qualified path */
                s = strdup(value);
        else /* on with only a tty file name, not a fully qualified path */
                s = path_join("/dev/", value);
        if (!s)
                return -ENOMEM;

        *console = s;
        return 0;
}