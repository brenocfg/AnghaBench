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
typedef  int /*<<< orphan*/  Set ;

/* Variables and functions */
 int log_oom () ; 
 scalar_t__ set_get (int /*<<< orphan*/ *,char*) ; 
 char* strndupa (char const*,size_t) ; 

__attribute__((used)) static int field_set_test(Set *fields, const char *name, size_t n) {
        char *s = NULL;

        if (!fields)
                return 1;

        s = strndupa(name, n);
        if (!s)
                return log_oom();

        return set_get(fields, s) ? 1 : 0;
}