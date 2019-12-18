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
typedef  char const Set ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int set_consume (char const*,char*) ; 
 scalar_t__ set_contains (char const*,char*) ; 
 char* strdup (char const*) ; 

int set_put_strdup(Set *s, const char *p) {
        char *c;

        assert(s);
        assert(p);

        if (set_contains(s, (char*) p))
                return 0;

        c = strdup(p);
        if (!c)
                return -ENOMEM;

        return set_consume(s, c);
}