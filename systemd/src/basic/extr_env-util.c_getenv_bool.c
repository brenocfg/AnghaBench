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
 int ENXIO ; 
 char* getenv (char const*) ; 
 int parse_boolean (char const*) ; 

int getenv_bool(const char *p) {
        const char *e;

        e = getenv(p);
        if (!e)
                return -ENXIO;

        return parse_boolean(e);
}