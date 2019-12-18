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
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static char* keyval(const char *str, const char **key, const char **val) {
        char *buf, *pos;

        buf = strdup(str);
        if (!buf)
                return NULL;

        pos = strchr(buf, '=');
        if (pos) {
                pos[0] = 0;
                pos++;
        }

        *key = buf;
        *val = pos;

        return buf;
}