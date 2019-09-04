#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int StructMembers; int /*<<< orphan*/  Name; } ;
struct ctab_constant {TYPE_2__ desc; struct ctab_constant* constants; } ;
struct TYPE_3__ {int Constants; } ;
struct ID3DXConstantTableImpl {struct ctab_constant* constants; TYPE_1__ desc; } ;
typedef  int UINT ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  debugstr_a (char const*) ; 
 struct ctab_constant* get_constant_element_by_name (struct ctab_constant*,char const*) ; 
 int strcspn (char const*,char*) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static struct ctab_constant *get_constant_by_name(struct ID3DXConstantTableImpl *table,
        struct ctab_constant *constant, const char *name)
{
    UINT i, count, length;
    struct ctab_constant *handles;
    const char *part;

    TRACE("table %p, constant %p, name %s\n", table, constant, debugstr_a(name));

    if (!name || !*name) return NULL;

    if (!constant)
    {
        count = table->desc.Constants;
        handles = table->constants;
    }
    else
    {
        count = constant->desc.StructMembers;
        handles = constant->constants;
    }

    length = strcspn(name, "[.");
    part = name + length;

    for (i = 0; i < count; i++)
    {
        if (strlen(handles[i].desc.Name) == length && !strncmp(handles[i].desc.Name, name, length))
        {
            switch (*part++)
            {
                case '.':
                    return get_constant_by_name(NULL, &handles[i], part);

                case '[':
                    return get_constant_element_by_name(&handles[i], part);

                default:
                    TRACE("Returning parameter %p\n", &handles[i]);
                    return &handles[i];
            }
        }
    }

    TRACE("Constant not found\n");
    return NULL;
}