#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wined3d_shader_tgsm {unsigned int size; unsigned int stride; } ;
struct TYPE_2__ {scalar_t__ type; } ;
struct wined3d_shader_reg_maps {struct wined3d_shader_tgsm* tgsm; int /*<<< orphan*/  tgsm_count; int /*<<< orphan*/  tgsm_capacity; TYPE_1__ shader_version; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,unsigned int) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 unsigned int MAX_TGSM_REGISTERS ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ WINED3D_SHADER_TYPE_COMPUTE ; 
 int /*<<< orphan*/  max (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_array_reserve (void**,int /*<<< orphan*/ *,unsigned int,int) ; 

__attribute__((used)) static HRESULT shader_reg_maps_add_tgsm(struct wined3d_shader_reg_maps *reg_maps,
        unsigned int register_idx, unsigned int size, unsigned int stride)
{
    struct wined3d_shader_tgsm *tgsm;

    if (register_idx >= MAX_TGSM_REGISTERS)
    {
        ERR("Invalid TGSM register index %u.\n", register_idx);
        return S_OK;
    }
    if (reg_maps->shader_version.type != WINED3D_SHADER_TYPE_COMPUTE)
    {
        FIXME("TGSM declarations are allowed only in compute shaders.\n");
        return S_OK;
    }

    if (!wined3d_array_reserve((void **)&reg_maps->tgsm, &reg_maps->tgsm_capacity,
            register_idx + 1, sizeof(*reg_maps->tgsm)))
        return E_OUTOFMEMORY;

    reg_maps->tgsm_count = max(register_idx + 1, reg_maps->tgsm_count);
    tgsm = &reg_maps->tgsm[register_idx];
    tgsm->size = size;
    tgsm->stride = stride;
    return S_OK;
}