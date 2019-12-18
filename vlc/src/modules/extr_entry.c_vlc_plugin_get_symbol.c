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
struct vlc_plugin_symbol {void* addr; } ;

/* Variables and functions */
 void** tfind (char const**,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_plugin_symbol_compare ; 

__attribute__((used)) static int vlc_plugin_get_symbol(void *root, const char *name,
                                 void **restrict addrp)
{
    if (name == NULL)
    {
        *addrp = NULL;
        return 0;
    }

    const void **symp = tfind(&name, &root, vlc_plugin_symbol_compare);

    if (symp == NULL)
        return -1;

    const struct vlc_plugin_symbol *sym = *symp;

    *addrp = sym->addr;
    return 0;
}