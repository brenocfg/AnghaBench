#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ID3DXEffectImpl {int /*<<< orphan*/  device; scalar_t__ manager; TYPE_2__* pool; int /*<<< orphan*/  base_effect; } ;
struct TYPE_4__ {TYPE_1__* lpVtbl; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* Release ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IDirect3DDevice9_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IUnknown_Release (scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,struct ID3DXEffectImpl*) ; 
 int /*<<< orphan*/  d3dx9_base_effect_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void free_effect(struct ID3DXEffectImpl *effect)
{
    TRACE("Free effect %p\n", effect);

    d3dx9_base_effect_cleanup(&effect->base_effect);

    if (effect->pool)
    {
        effect->pool->lpVtbl->Release(effect->pool);
    }

    if (effect->manager)
    {
        IUnknown_Release(effect->manager);
    }

    IDirect3DDevice9_Release(effect->device);
}