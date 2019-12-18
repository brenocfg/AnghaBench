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
typedef  char const OrderedSet ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int ordered_set_consume (char const*,char*) ; 
 char* strdup (char const*) ; 

int ordered_set_put_strdup(OrderedSet *s, const char *p) {
        char *c;
        int r;

        assert(s);
        assert(p);

        c = strdup(p);
        if (!c)
                return -ENOMEM;

        r = ordered_set_consume(s, c);
        if (r == -EEXIST)
                return 0;

        return r;
}