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
 int /*<<< orphan*/  assert (char***) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memmove (char**,char**,size_t) ; 
 char** reallocarray (char**,size_t,int) ; 
 char* strdup (char const*) ; 
 size_t strv_length (char**) ; 

int strv_extend_front(char ***l, const char *value) {
        size_t n, m;
        char *v, **c;

        assert(l);

        /* Like strv_extend(), but prepends rather than appends the new entry */

        if (!value)
                return 0;

        n = strv_length(*l);

        /* Increase and overflow check. */
        m = n + 2;
        if (m < n)
                return -ENOMEM;

        v = strdup(value);
        if (!v)
                return -ENOMEM;

        c = reallocarray(*l, m, sizeof(char*));
        if (!c) {
                free(v);
                return -ENOMEM;
        }

        memmove(c+1, c, n * sizeof(char*));
        c[0] = v;
        c[n+1] = NULL;

        *l = c;
        return 0;
}