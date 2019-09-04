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
struct d3dx_parameter {scalar_t__ type; scalar_t__ data; int /*<<< orphan*/  element_count; } ;
struct d3dx9_base_effect {int dummy; } ;
struct IDirect3DPixelShader9 {int dummy; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  D3DXHANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  D3DERR_INVALIDCALL ; 
 scalar_t__ D3DXPT_PIXELSHADER ; 
 int /*<<< orphan*/  D3D_OK ; 
 int /*<<< orphan*/  IDirect3DPixelShader9_AddRef (struct IDirect3DPixelShader9*) ; 
 int /*<<< orphan*/  TRACE (char*,struct IDirect3DPixelShader9*) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 struct d3dx_parameter* get_valid_parameter (struct d3dx9_base_effect*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT d3dx9_base_effect_get_pixel_shader(struct d3dx9_base_effect *base,
        D3DXHANDLE parameter, struct IDirect3DPixelShader9 **shader)
{
    struct d3dx_parameter *param = get_valid_parameter(base, parameter);

    if (shader && param && !param->element_count && param->type == D3DXPT_PIXELSHADER)
    {
        if ((*shader = *(struct IDirect3DPixelShader9 **)param->data))
            IDirect3DPixelShader9_AddRef(*shader);
        TRACE("Returning %p.\n", *shader);
        return D3D_OK;
    }

    WARN("Parameter not found.\n");

    return D3DERR_INVALIDCALL;
}