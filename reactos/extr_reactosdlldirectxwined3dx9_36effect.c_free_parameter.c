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
struct d3dx_parameter {unsigned int element_count; unsigned int member_count; struct d3dx_parameter* semantic; struct d3dx_parameter* name; struct d3dx_parameter* members; scalar_t__ param_eval; int /*<<< orphan*/  type; } ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct d3dx_parameter*) ; 
 int /*<<< orphan*/  TRACE (char*,struct d3dx_parameter*,struct d3dx_parameter*,int /*<<< orphan*/ ,int,int) ; 
 int TRUE ; 
 int /*<<< orphan*/  d3dx_free_param_eval (scalar_t__) ; 
 int /*<<< orphan*/  debug_d3dxparameter_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_parameter_data (struct d3dx_parameter*,int) ; 

__attribute__((used)) static void free_parameter(struct d3dx_parameter *param, BOOL element, BOOL child)
{
    unsigned int i;

    TRACE("Free parameter %p, name %s, type %s, element %#x, child %#x.\n", param, param->name,
            debug_d3dxparameter_type(param->type), element, child);

    if (param->param_eval)
        d3dx_free_param_eval(param->param_eval);

    if (param->members)
    {
        unsigned int count = param->element_count ? param->element_count : param->member_count;

        for (i = 0; i < count; ++i)
            free_parameter(&param->members[i], param->element_count != 0, TRUE);
        HeapFree(GetProcessHeap(), 0, param->members);
    }

    free_parameter_data(param, child);

    /* only the parent has to release name and semantic */
    if (!element)
    {
        HeapFree(GetProcessHeap(), 0, param->name);
        HeapFree(GetProcessHeap(), 0, param->semantic);
    }
}