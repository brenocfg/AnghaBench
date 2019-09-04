#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int /*<<< orphan*/ * lpVtbl; } ;
struct d3drm_texture {int /*<<< orphan*/  obj; int /*<<< orphan*/ * d3drm; TYPE_1__ IDirect3DRMTexture3_iface; TYPE_3__ IDirect3DRMTexture2_iface; TYPE_2__ IDirect3DRMTexture_iface; } ;
typedef  int /*<<< orphan*/  IDirect3DRM ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  D3DRM_OK ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  TRACE (char*,struct d3drm_texture**) ; 
 int /*<<< orphan*/  d3drm_object_init (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  d3drm_texture1_vtbl ; 
 int /*<<< orphan*/  d3drm_texture2_vtbl ; 
 int /*<<< orphan*/  d3drm_texture3_vtbl ; 
 struct d3drm_texture* heap_alloc_zero (int) ; 

HRESULT d3drm_texture_create(struct d3drm_texture **texture, IDirect3DRM *d3drm)
{
    static const char classname[] = "Texture";
    struct d3drm_texture *object;

    TRACE("texture %p.\n", texture);

    if (!(object = heap_alloc_zero(sizeof(*object))))
        return E_OUTOFMEMORY;

    object->IDirect3DRMTexture_iface.lpVtbl = &d3drm_texture1_vtbl;
    object->IDirect3DRMTexture2_iface.lpVtbl = &d3drm_texture2_vtbl;
    object->IDirect3DRMTexture3_iface.lpVtbl = &d3drm_texture3_vtbl;
    object->d3drm = d3drm;

    d3drm_object_init(&object->obj, classname);

    *texture = object;

    return D3DRM_OK;
}