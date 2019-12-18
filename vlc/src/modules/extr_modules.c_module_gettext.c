#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* plugin; } ;
typedef  TYPE_2__ module_t ;
struct TYPE_4__ {char* textdomain; } ;

/* Variables and functions */
 char const* PACKAGE_NAME ; 
 char const* dgettext (char const*,char const*) ; 
 scalar_t__ unlikely (int) ; 

const char *module_gettext (const module_t *m, const char *str)
{
    if (unlikely(str == NULL || *str == '\0'))
        return "";
#ifdef ENABLE_NLS
    const char *domain = m->plugin->textdomain;
    return dgettext ((domain != NULL) ? domain : PACKAGE_NAME, str);
#else
    (void)m;
    return str;
#endif
}