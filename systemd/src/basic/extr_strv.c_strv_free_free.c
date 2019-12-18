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
 char*** mfree (char***) ; 
 int /*<<< orphan*/  strv_free (char**) ; 

char ***strv_free_free(char ***l) {
        char ***i;

        if (!l)
                return NULL;

        for (i = l; *i; i++)
                strv_free(*i);

        return mfree(l);
}