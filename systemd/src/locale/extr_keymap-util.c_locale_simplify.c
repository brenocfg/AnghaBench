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
 int VARIABLE_LANG ; 
 int _VARIABLE_LC_MAX ; 
 scalar_t__ isempty (char*) ; 
 char* mfree (char*) ; 
 scalar_t__ streq_ptr (char*,char*) ; 

void locale_simplify(char *locale[_VARIABLE_LC_MAX]) {
        int p;

        for (p = VARIABLE_LANG+1; p < _VARIABLE_LC_MAX; p++)
                if (isempty(locale[p]) || streq_ptr(locale[VARIABLE_LANG], locale[p]))
                        locale[p] = mfree(locale[p]);
}