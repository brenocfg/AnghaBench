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
struct d3dx_parameter {int dummy; } ;
struct d3dx9_base_effect {int dummy; } ;
typedef  int /*<<< orphan*/  D3DXHANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 struct d3dx_parameter* get_parameter_by_name (struct d3dx9_base_effect*,struct d3dx_parameter*,char const*) ; 
 int /*<<< orphan*/  get_parameter_handle (struct d3dx_parameter*) ; 
 struct d3dx_parameter* get_valid_parameter (struct d3dx9_base_effect*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static D3DXHANDLE d3dx9_base_effect_get_parameter_by_name(struct d3dx9_base_effect *base,
        D3DXHANDLE parameter, const char *name)
{
    struct d3dx_parameter *param = get_valid_parameter(base, parameter);
    D3DXHANDLE handle;

    if (!name)
    {
        handle = get_parameter_handle(param);
        TRACE("Returning parameter %p.\n", handle);
        return handle;
    }

    handle = get_parameter_handle(get_parameter_by_name(base, param, name));
    TRACE("Returning parameter %p.\n", handle);

    return handle;
}