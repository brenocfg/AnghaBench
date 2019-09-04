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
struct d3dx_technique {unsigned int pass_count; struct d3dx_pass* passes; } ;
struct d3dx_pass {int /*<<< orphan*/  name; } ;
struct d3dx9_base_effect {int dummy; } ;
typedef  int /*<<< orphan*/ * D3DXHANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,struct d3dx_pass*) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/ * get_pass_handle (struct d3dx_pass*) ; 
 struct d3dx_technique* get_valid_technique (struct d3dx9_base_effect*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static D3DXHANDLE d3dx9_base_effect_get_pass_by_name(struct d3dx9_base_effect *base,
        D3DXHANDLE technique, const char *name)
{
    struct d3dx_technique *tech = get_valid_technique(base, technique);

    if (tech && name)
    {
        unsigned int i;

        for (i = 0; i < tech->pass_count; ++i)
        {
            struct d3dx_pass *pass = &tech->passes[i];

            if (!strcmp(pass->name, name))
            {
                TRACE("Returning pass %p\n", pass);
                return get_pass_handle(pass);
            }
        }
    }

    WARN("Pass not found.\n");

    return NULL;
}