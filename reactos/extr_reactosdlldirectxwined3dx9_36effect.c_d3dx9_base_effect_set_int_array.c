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
struct d3dx_parameter {int bytes; int class; int /*<<< orphan*/  type; scalar_t__ data; } ;
struct d3dx9_base_effect {int dummy; } ;
typedef  size_t UINT ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  D3DXHANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  D3DERR_INVALIDCALL ; 
#define  D3DXPC_MATRIX_ROWS 132 
#define  D3DXPC_OBJECT 131 
#define  D3DXPC_SCALAR 130 
#define  D3DXPC_STRUCT 129 
#define  D3DXPC_VECTOR 128 
 int /*<<< orphan*/  D3DXPT_INT ; 
 int /*<<< orphan*/  D3D_OK ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  debug_d3dxparameter_class (int) ; 
 struct d3dx_parameter* get_valid_parameter (struct d3dx9_base_effect*,int /*<<< orphan*/ ) ; 
 size_t min (size_t,int) ; 
 int /*<<< orphan*/  set_dirty (struct d3dx_parameter*) ; 
 int /*<<< orphan*/  set_number (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT d3dx9_base_effect_set_int_array(struct d3dx9_base_effect *base,
        D3DXHANDLE parameter, const INT *n, UINT count)
{
    struct d3dx_parameter *param = get_valid_parameter(base, parameter);

    if (param)
    {
        UINT i, size = min(count, param->bytes / sizeof(DWORD));

        TRACE("Class %s\n", debug_d3dxparameter_class(param->class));

        switch (param->class)
        {
            case D3DXPC_SCALAR:
            case D3DXPC_VECTOR:
            case D3DXPC_MATRIX_ROWS:
                for (i = 0; i < size; ++i)
                {
                    set_number((DWORD *)param->data + i, param->type, &n[i], D3DXPT_INT);
                }
                set_dirty(param);
                return D3D_OK;

            case D3DXPC_OBJECT:
            case D3DXPC_STRUCT:
                break;

            default:
                FIXME("Unhandled class %s\n", debug_d3dxparameter_class(param->class));
                break;
        }
    }

    WARN("Parameter not found.\n");

    return D3DERR_INVALIDCALL;
}