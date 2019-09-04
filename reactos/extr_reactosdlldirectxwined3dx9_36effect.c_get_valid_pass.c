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
struct d3dx_pass {int dummy; } ;
struct d3dx9_base_effect {unsigned int technique_count; struct d3dx_technique* techniques; } ;
typedef  scalar_t__ D3DXHANDLE ;

/* Variables and functions */
 scalar_t__ get_pass_handle (struct d3dx_pass*) ; 

__attribute__((used)) static struct d3dx_pass *get_valid_pass(struct d3dx9_base_effect *base, D3DXHANDLE pass)
{
    unsigned int i, k;

    for (i = 0; i < base->technique_count; ++i)
    {
        struct d3dx_technique *technique = &base->techniques[i];

        for (k = 0; k < technique->pass_count; ++k)
        {
            if (get_pass_handle(&technique->passes[k]) == pass)
                return &technique->passes[k];
        }
    }

    return NULL;
}