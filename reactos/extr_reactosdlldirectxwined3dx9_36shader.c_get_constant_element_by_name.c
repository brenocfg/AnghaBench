#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t Elements; } ;
struct ctab_constant {struct ctab_constant* constants; TYPE_1__ desc; } ;
typedef  size_t UINT ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,char const) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 size_t atoi (char const*) ; 
 int /*<<< orphan*/  debugstr_a (char const*) ; 
 struct ctab_constant* get_constant_by_name (int /*<<< orphan*/ *,struct ctab_constant*,char const*) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static struct ctab_constant *get_constant_element_by_name(struct ctab_constant *constant, const char *name)
{
    const char *part;
    UINT element;

    TRACE("constant %p, name %s\n", constant, debugstr_a(name));

    if (!name || !*name) return NULL;

    element = atoi(name);
    part = strchr(name, ']') + 1;

    if (constant->desc.Elements > element)
    {
        struct ctab_constant *c = constant->constants ? &constant->constants[element] : constant;

        switch (*part++)
        {
            case '.':
                return get_constant_by_name(NULL, c, part);

            case '[':
                return get_constant_element_by_name(c, part);

            case '\0':
                TRACE("Returning parameter %p\n", c);
                return c;

            default:
                FIXME("Unhandled case \"%c\"\n", *--part);
                break;
        }
    }

    TRACE("Constant not found\n");
    return NULL;
}