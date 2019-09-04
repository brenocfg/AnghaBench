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
struct d3dx_parameter {int rows; int columns; int /*<<< orphan*/  type; int /*<<< orphan*/  data; int /*<<< orphan*/  element_count; } ;
struct d3dx9_base_effect {int dummy; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  D3DXHANDLE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  D3DERR_INVALIDCALL ; 
 int /*<<< orphan*/  D3DXPT_BOOL ; 
 int /*<<< orphan*/  D3D_OK ; 
 int /*<<< orphan*/  TRACE (char*,char*) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 struct d3dx_parameter* get_valid_parameter (struct d3dx9_base_effect*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_number (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT d3dx9_base_effect_get_bool(struct d3dx9_base_effect *base, D3DXHANDLE parameter, BOOL *b)
{
    struct d3dx_parameter *param = get_valid_parameter(base, parameter);

    if (b && param && !param->element_count && param->rows == 1 && param->columns == 1)
    {
        set_number(b, D3DXPT_BOOL, param->data, param->type);
        TRACE("Returning %s\n", *b ? "TRUE" : "FALSE");
        return D3D_OK;
    }

    WARN("Parameter not found.\n");

    return D3DERR_INVALIDCALL;
}