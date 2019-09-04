#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct d3dx_state {size_t operation; } ;
struct d3dx_pass {unsigned int state_count; struct d3dx_state* states; int /*<<< orphan*/  annotation_count; int /*<<< orphan*/  name; } ;
struct d3dx_parameter {int object_id; } ;
struct d3dx9_base_effect {int flags; TYPE_1__* objects; } ;
struct TYPE_7__ {scalar_t__ class; } ;
struct TYPE_6__ {int /*<<< orphan*/ * pPixelShaderFunction; int /*<<< orphan*/ * pVertexShaderFunction; int /*<<< orphan*/  Annotations; int /*<<< orphan*/  Name; } ;
struct TYPE_5__ {int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ D3DXPASS_DESC ;
typedef  int /*<<< orphan*/  D3DXHANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  D3DERR_INVALIDCALL ; 
 int D3DXFX_NOT_CLONEABLE ; 
 int /*<<< orphan*/  D3D_OK ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SC_PIXELSHADER ; 
 scalar_t__ SC_VERTEXSHADER ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  d3dx9_get_param_value_ptr (struct d3dx_pass*,struct d3dx_state*,void**,struct d3dx_parameter**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct d3dx_pass* get_valid_pass (struct d3dx9_base_effect*,int /*<<< orphan*/ ) ; 
 TYPE_3__* state_table ; 

__attribute__((used)) static HRESULT d3dx9_base_effect_get_pass_desc(struct d3dx9_base_effect *base,
        D3DXHANDLE pass_handle, D3DXPASS_DESC *desc)
{
    struct d3dx_pass *pass = get_valid_pass(base, pass_handle);
    unsigned int i;

    if (!desc || !pass)
    {
        WARN("Invalid argument specified.\n");
        return D3DERR_INVALIDCALL;
    }

    desc->Name = pass->name;
    desc->Annotations = pass->annotation_count;

    desc->pVertexShaderFunction = NULL;
    desc->pPixelShaderFunction = NULL;

    if (base->flags & D3DXFX_NOT_CLONEABLE)
        return D3D_OK;

    for (i = 0; i < pass->state_count; ++i)
    {
        struct d3dx_state *state = &pass->states[i];

        if (state_table[state->operation].class == SC_VERTEXSHADER
                || state_table[state->operation].class == SC_PIXELSHADER)
        {
            struct d3dx_parameter *param;
            void *param_value;
            BOOL param_dirty;
            HRESULT hr;
            void *data;

            if (FAILED(hr = d3dx9_get_param_value_ptr(pass, &pass->states[i], &param_value, &param,
                    FALSE, &param_dirty)))
                return hr;

            data = param->object_id ? base->objects[param->object_id].data : NULL;
            if (state_table[state->operation].class == SC_VERTEXSHADER)
                desc->pVertexShaderFunction = data;
            else
                desc->pPixelShaderFunction = data;
        }
    }

    return D3D_OK;
}