#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int i_shortcuts; char** pp_shortcuts; } ;
typedef  TYPE_1__ module_t ;

/* Variables and functions */
 char* module_get_object (TYPE_1__ const*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/ * strstr (char const*,char const*) ; 

__attribute__((used)) static bool module_match(const module_t *m, const char *pattern, bool strict)
{
    if (pattern == NULL)
        return true;

    const char *objname = module_get_object(m);

    if (strict ? (strcmp(objname, pattern) == 0)
               : (strstr(objname, pattern) != NULL))
        return true;

    for (unsigned i = 0; i < m->i_shortcuts; i++)
    {
        const char *shortcut = m->pp_shortcuts[i];

        if (strict ? (strcmp(shortcut, pattern) == 0)
                   : (strstr(shortcut, pattern) != NULL))
            return true;
    }
    return false;
}