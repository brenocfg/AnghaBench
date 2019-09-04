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
typedef  scalar_t__ (* walk_parameter_dep_func ) (void*,struct d3dx_parameter*) ;
struct d3dx_parameter {unsigned int element_count; unsigned int member_count; struct d3dx_parameter* members; } ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static BOOL walk_parameter_tree(struct d3dx_parameter *param, walk_parameter_dep_func param_func,
        void *data)
{
    unsigned int i;
    unsigned int member_count;

    if (param_func(data, param))
        return TRUE;

    member_count = param->element_count ? param->element_count : param->member_count;
    for (i = 0; i < member_count; ++i)
    {
        if (walk_parameter_tree(&param->members[i], param_func, data))
            return TRUE;
    }
    return FALSE;
}