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
struct d3dx_parameter {int columns; int rows; int /*<<< orphan*/  type; scalar_t__ data; int /*<<< orphan*/  element_count; } ;
struct d3dx9_base_effect {int dummy; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  D3DXHANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  D3DERR_INVALIDCALL ; 
 int /*<<< orphan*/  D3DXPT_FLOAT ; 
 int /*<<< orphan*/  D3D_OK ; 
 int /*<<< orphan*/  TRACE (char*,float) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 struct d3dx_parameter* get_valid_parameter (struct d3dx9_base_effect*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_number (float*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT d3dx9_base_effect_get_float(struct d3dx9_base_effect *base, D3DXHANDLE parameter, float *f)
{
    struct d3dx_parameter *param = get_valid_parameter(base, parameter);

    if (f && param && !param->element_count && param->columns == 1 && param->rows == 1)
    {
        set_number(f, D3DXPT_FLOAT, (DWORD *)param->data, param->type);
        TRACE("Returning %f\n", *f);
        return D3D_OK;
    }

    WARN("Parameter not found.\n");

    return D3DERR_INVALIDCALL;
}