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
struct d3dx_technique {int /*<<< orphan*/  name; } ;
struct d3dx9_base_effect {size_t technique_count; struct d3dx_technique* techniques; } ;
typedef  size_t UINT ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct d3dx_technique *get_technique_by_name(struct d3dx9_base_effect *base, const char *name)
{
    UINT i;

    if (!name) return NULL;

    for (i = 0; i < base->technique_count; ++i)
    {
        if (!strcmp(base->techniques[i].name, name))
            return &base->techniques[i];
    }

    return NULL;
}