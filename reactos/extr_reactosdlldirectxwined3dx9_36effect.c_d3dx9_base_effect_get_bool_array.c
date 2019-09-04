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
struct d3dx_parameter {scalar_t__ class; int bytes; int /*<<< orphan*/  type; scalar_t__ data; } ;
struct d3dx9_base_effect {int dummy; } ;
typedef  size_t UINT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  D3DXHANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  D3DERR_INVALIDCALL ; 
 scalar_t__ D3DXPC_MATRIX_COLUMNS ; 
 scalar_t__ D3DXPC_MATRIX_ROWS ; 
 scalar_t__ D3DXPC_SCALAR ; 
 scalar_t__ D3DXPC_VECTOR ; 
 int /*<<< orphan*/  D3DXPT_BOOL ; 
 int /*<<< orphan*/  D3D_OK ; 
 int /*<<< orphan*/  WARN (char*) ; 
 struct d3dx_parameter* get_valid_parameter (struct d3dx9_base_effect*,int /*<<< orphan*/ ) ; 
 size_t min (size_t,int) ; 
 int /*<<< orphan*/  set_number (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT d3dx9_base_effect_get_bool_array(struct d3dx9_base_effect *base,
        D3DXHANDLE parameter, BOOL *b, UINT count)
{
    struct d3dx_parameter *param = get_valid_parameter(base, parameter);

    if (b && param && (param->class == D3DXPC_SCALAR
            || param->class == D3DXPC_VECTOR
            || param->class == D3DXPC_MATRIX_ROWS
            || param->class == D3DXPC_MATRIX_COLUMNS))
    {
        UINT i, size = min(count, param->bytes / sizeof(DWORD));

        for (i = 0; i < size; ++i)
        {
            set_number(&b[i], D3DXPT_BOOL, (DWORD *)param->data + i, param->type);
        }
        return D3D_OK;
    }

    WARN("Parameter not found.\n");

    return D3DERR_INVALIDCALL;
}