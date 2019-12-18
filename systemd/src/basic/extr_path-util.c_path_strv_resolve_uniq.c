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
 int /*<<< orphan*/  path_strv_resolve (char**,char const*) ; 
 scalar_t__ strv_isempty (char**) ; 
 char** strv_uniq (char**) ; 

char **path_strv_resolve_uniq(char **l, const char *root) {

        if (strv_isempty(l))
                return l;

        if (!path_strv_resolve(l, root))
                return NULL;

        return strv_uniq(l);
}