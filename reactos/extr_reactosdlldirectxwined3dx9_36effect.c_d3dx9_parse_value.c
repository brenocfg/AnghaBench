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
struct d3dx_sampler {int dummy; } ;
struct d3dx_parameter {int element_count; int bytes; int class; unsigned int member_count; size_t object_id; int /*<<< orphan*/  type; struct d3dx_sampler* data; struct d3dx_parameter* members; } ;
struct d3dx_object {struct d3dx_parameter* param; } ;
struct d3dx9_base_effect {int dummy; } ;
typedef  int UINT ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
#define  D3DXPC_MATRIX_COLUMNS 146 
#define  D3DXPC_MATRIX_ROWS 145 
#define  D3DXPC_OBJECT 144 
#define  D3DXPC_SCALAR 143 
#define  D3DXPC_STRUCT 142 
#define  D3DXPC_VECTOR 141 
#define  D3DXPT_PIXELSHADER 140 
#define  D3DXPT_SAMPLER 139 
#define  D3DXPT_SAMPLER1D 138 
#define  D3DXPT_SAMPLER2D 137 
#define  D3DXPT_SAMPLER3D 136 
#define  D3DXPT_SAMPLERCUBE 135 
#define  D3DXPT_STRING 134 
#define  D3DXPT_TEXTURE 133 
#define  D3DXPT_TEXTURE1D 132 
#define  D3DXPT_TEXTURE2D 131 
#define  D3DXPT_TEXTURE3D 130 
#define  D3DXPT_TEXTURECUBE 129 
#define  D3DXPT_VERTEXSHADER 128 
 scalar_t__ D3D_OK ; 
 scalar_t__ E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 struct d3dx_sampler* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct d3dx_sampler*) ; 
 int /*<<< orphan*/  TRACE (char*,size_t) ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 scalar_t__ d3dx9_parse_sampler (struct d3dx9_base_effect*,struct d3dx_sampler*,char const*,char const**,struct d3dx_object*) ; 
 int /*<<< orphan*/  debug_d3dxparameter_class (int) ; 
 int /*<<< orphan*/  debug_d3dxparameter_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_dword (char const**,size_t*) ; 

__attribute__((used)) static HRESULT d3dx9_parse_value(struct d3dx9_base_effect *base, struct d3dx_parameter *param,
        void *value, const char *data, const char **ptr, struct d3dx_object *objects)
{
    unsigned int i;
    HRESULT hr;
    UINT old_size = 0;

    if (param->element_count)
    {
        param->data = value;

        for (i = 0; i < param->element_count; ++i)
        {
            struct d3dx_parameter *member = &param->members[i];

            hr = d3dx9_parse_value(base, member, value ? (char *)value + old_size : NULL, data, ptr, objects);
            if (hr != D3D_OK)
            {
                WARN("Failed to parse value %u\n", i);
                return hr;
            }

            old_size += member->bytes;
        }

        return D3D_OK;
    }

    switch(param->class)
    {
        case D3DXPC_SCALAR:
        case D3DXPC_VECTOR:
        case D3DXPC_MATRIX_ROWS:
        case D3DXPC_MATRIX_COLUMNS:
            param->data = value;
            break;

        case D3DXPC_STRUCT:
            param->data = value;

            for (i = 0; i < param->member_count; ++i)
            {
                struct d3dx_parameter *member = &param->members[i];

                hr = d3dx9_parse_value(base, member, (char *)value + old_size, data, ptr, objects);
                if (hr != D3D_OK)
                {
                    WARN("Failed to parse value %u\n", i);
                    return hr;
                }

                old_size += member->bytes;
            }
            break;

        case D3DXPC_OBJECT:
            switch (param->type)
            {
                case D3DXPT_STRING:
                case D3DXPT_TEXTURE:
                case D3DXPT_TEXTURE1D:
                case D3DXPT_TEXTURE2D:
                case D3DXPT_TEXTURE3D:
                case D3DXPT_TEXTURECUBE:
                case D3DXPT_PIXELSHADER:
                case D3DXPT_VERTEXSHADER:
                    read_dword(ptr, &param->object_id);
                    TRACE("Id: %u\n", param->object_id);
                    objects[param->object_id].param = param;
                    param->data = value;
                    break;

                case D3DXPT_SAMPLER:
                case D3DXPT_SAMPLER1D:
                case D3DXPT_SAMPLER2D:
                case D3DXPT_SAMPLER3D:
                case D3DXPT_SAMPLERCUBE:
                {
                    struct d3dx_sampler *sampler;

                    sampler = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*sampler));
                    if (!sampler)
                        return E_OUTOFMEMORY;

                    hr = d3dx9_parse_sampler(base, sampler, data, ptr, objects);
                    if (hr != D3D_OK)
                    {
                        HeapFree(GetProcessHeap(), 0, sampler);
                        WARN("Failed to parse sampler\n");
                        return hr;
                    }

                    param->data = sampler;
                    break;
                }

                default:
                    FIXME("Unhandled type %s\n", debug_d3dxparameter_type(param->type));
                    break;
            }
            break;

        default:
            FIXME("Unhandled class %s\n", debug_d3dxparameter_class(param->class));
            break;
    }

    return D3D_OK;
}