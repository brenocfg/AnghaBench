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
typedef  size_t LocaleVariable ;

/* Variables and functions */
 size_t _VARIABLE_LC_MAX ; 
 char* mfree (char*) ; 

void locale_variables_free(char *l[_VARIABLE_LC_MAX]) {
        LocaleVariable i;

        if (!l)
                return;

        for (i = 0; i < _VARIABLE_LC_MAX; i++)
                l[i] = mfree(l[i]);
}