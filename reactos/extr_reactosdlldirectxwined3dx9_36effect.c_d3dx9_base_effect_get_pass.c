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
struct d3dx_technique {size_t pass_count; int /*<<< orphan*/ * passes; } ;
struct d3dx9_base_effect {int dummy; } ;
typedef  size_t UINT ;
typedef  int /*<<< orphan*/ * D3DXHANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/ * get_pass_handle (int /*<<< orphan*/ *) ; 
 struct d3dx_technique* get_valid_technique (struct d3dx9_base_effect*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static D3DXHANDLE d3dx9_base_effect_get_pass(struct d3dx9_base_effect *base,
        D3DXHANDLE technique, UINT index)
{
    struct d3dx_technique *tech = get_valid_technique(base, technique);

    if (tech && index < tech->pass_count)
    {
        TRACE("Returning pass %p\n", &tech->passes[index]);
        return get_pass_handle(&tech->passes[index]);
    }

    WARN("Pass not found.\n");

    return NULL;
}