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
 scalar_t__ free_and_strdup (char**,char const*) ; 
 int log_oom () ; 

__attribute__((used)) static inline int free_and_strdup_warn(char **p, const char *s) {
        if (free_and_strdup(p, s) < 0)
                return log_oom();
        return 0;
}