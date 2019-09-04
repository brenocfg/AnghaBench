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
struct d3dx_parameter {scalar_t__ element_count; int class; int columns; float* data; int /*<<< orphan*/ * members; int /*<<< orphan*/  type; } ;
struct d3dx9_base_effect {int dummy; } ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  D3DXVECTOR4 ;
typedef  int /*<<< orphan*/  D3DXHANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  D3DERR_INVALIDCALL ; 
#define  D3DXPC_MATRIX_ROWS 132 
#define  D3DXPC_OBJECT 131 
#define  D3DXPC_SCALAR 130 
#define  D3DXPC_STRUCT 129 
#define  D3DXPC_VECTOR 128 
 int /*<<< orphan*/  D3DXPT_FLOAT ; 
 int /*<<< orphan*/  D3D_OK ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  debug_d3dxparameter_class (int) ; 
 struct d3dx_parameter* get_valid_parameter (struct d3dx9_base_effect*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (float*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  set_dirty (struct d3dx_parameter*) ; 
 int /*<<< orphan*/  set_vector (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static HRESULT d3dx9_base_effect_set_vector_array(struct d3dx9_base_effect *base,
        D3DXHANDLE parameter, const D3DXVECTOR4 *vector, UINT count)
{
    struct d3dx_parameter *param = get_valid_parameter(base, parameter);

    if (param && param->element_count && param->element_count >= count)
    {
        UINT i;

        TRACE("Class %s\n", debug_d3dxparameter_class(param->class));

        switch (param->class)
        {
            case D3DXPC_VECTOR:
                set_dirty(param);
                if (param->type == D3DXPT_FLOAT)
                {
                    if (param->columns == 4)
                        memcpy(param->data, vector, count * 4 * sizeof(float));
                    else
                        for (i = 0; i < count; ++i)
                            memcpy((float *)param->data + param->columns * i, vector + i,
                                    param->columns * sizeof(float));
                    return D3D_OK;
                }

                for (i = 0; i < count; ++i)
                {
                    set_vector(&param->members[i], &vector[i]);
                }
                return D3D_OK;

            case D3DXPC_SCALAR:
            case D3DXPC_MATRIX_ROWS:
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