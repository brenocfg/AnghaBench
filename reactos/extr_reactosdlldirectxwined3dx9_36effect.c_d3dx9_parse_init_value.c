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
struct d3dx_parameter {int class; scalar_t__ bytes; } ;
struct d3dx_object {int dummy; } ;
struct d3dx9_base_effect {int dummy; } ;
typedef  scalar_t__ UINT ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
#define  D3DXPC_MATRIX_COLUMNS 133 
#define  D3DXPC_MATRIX_ROWS 132 
#define  D3DXPC_OBJECT 131 
#define  D3DXPC_SCALAR 130 
#define  D3DXPC_STRUCT 129 
#define  D3DXPC_VECTOR 128 
 scalar_t__ D3D_OK ; 
 int /*<<< orphan*/  ERR (char*) ; 
 scalar_t__ E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 scalar_t__ d3dx9_parse_value (struct d3dx9_base_effect*,struct d3dx_parameter*,void*,char const*,char const**,struct d3dx_object*) ; 
 int /*<<< orphan*/  debug_d3dxparameter_class (int) ; 
 scalar_t__ debugstr_an (char const*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (void*,char const*,scalar_t__) ; 

__attribute__((used)) static HRESULT d3dx9_parse_init_value(struct d3dx9_base_effect *base, struct d3dx_parameter *param,
        const char *data, const char *ptr, struct d3dx_object *objects)
{
    UINT size = param->bytes;
    HRESULT hr;
    void *value = NULL;

    TRACE("param size: %u\n", size);

    if (size)
    {
        value = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
        if (!value)
        {
            ERR("Failed to allocate data memory.\n");
            return E_OUTOFMEMORY;
        }

        switch(param->class)
        {
            case D3DXPC_OBJECT:
                break;

            case D3DXPC_SCALAR:
            case D3DXPC_VECTOR:
            case D3DXPC_MATRIX_ROWS:
            case D3DXPC_MATRIX_COLUMNS:
            case D3DXPC_STRUCT:
                TRACE("Data: %s.\n", debugstr_an(ptr, size));
                memcpy(value, ptr, size);
                break;

            default:
                FIXME("Unhandled class %s\n", debug_d3dxparameter_class(param->class));
                break;
        }
    }

    hr = d3dx9_parse_value(base, param, value, data, &ptr, objects);
    if (hr != D3D_OK)
    {
        WARN("Failed to parse value\n");
        HeapFree(GetProcessHeap(), 0, value);
        return hr;
    }

    return D3D_OK;
}