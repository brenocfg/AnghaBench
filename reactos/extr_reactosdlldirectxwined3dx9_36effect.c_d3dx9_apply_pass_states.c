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
struct d3dx_pass {unsigned int state_count; int /*<<< orphan*/  update_version; int /*<<< orphan*/ * states; } ;
struct ID3DXEffectImpl {int light_updated; scalar_t__ material_updated; int /*<<< orphan*/  current_material; int /*<<< orphan*/ * current_light; int /*<<< orphan*/  base_effect; } ;
typedef  int /*<<< orphan*/  ULONG64 ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  D3D_OK ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SET_D3D_STATE (struct ID3DXEffectImpl*,int /*<<< orphan*/ ,unsigned int,...) ; 
 int /*<<< orphan*/  SetLight ; 
 int /*<<< orphan*/  SetMaterial ; 
 int /*<<< orphan*/  TRACE (char*,struct ID3DXEffectImpl*,struct d3dx_pass*,unsigned int) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3dx9_apply_state (struct ID3DXEffectImpl*,struct d3dx_pass*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next_effect_update_version (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT d3dx9_apply_pass_states(struct ID3DXEffectImpl *effect, struct d3dx_pass *pass, BOOL update_all)
{
    unsigned int i;
    HRESULT ret;
    HRESULT hr;
    ULONG64 new_update_version = next_effect_update_version(&effect->base_effect);

    TRACE("effect %p, pass %p, state_count %u.\n", effect, pass, pass->state_count);

    ret = D3D_OK;
    for (i = 0; i < pass->state_count; ++i)
    {
        if (FAILED(hr = d3dx9_apply_state(effect, pass, &pass->states[i], ~0u, update_all)))
        {
            WARN("Error applying state, hr %#x.\n", hr);
            ret = hr;
        }
    }

    if (effect->light_updated)
    {
        for (i = 0; i < ARRAY_SIZE(effect->current_light); ++i)
        {
            if ((effect->light_updated & (1u << i))
                    && FAILED(hr = SET_D3D_STATE(effect, SetLight, i, &effect->current_light[i])))
            {
                WARN("Error setting light, hr %#x.\n", hr);
                ret = hr;
            }
        }
        effect->light_updated = 0;
    }

    if (effect->material_updated
            && FAILED(hr = SET_D3D_STATE(effect, SetMaterial, &effect->current_material)))
    {
        WARN("Error setting material, hr %#x.\n", hr);
        ret = hr;
    }
    effect->material_updated = FALSE;

    pass->update_version = new_update_version;
    return ret;
}