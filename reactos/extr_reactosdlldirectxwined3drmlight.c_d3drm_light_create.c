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
struct TYPE_2__ {int /*<<< orphan*/ * lpVtbl; } ;
struct d3drm_light {int ref; int /*<<< orphan*/  obj; int /*<<< orphan*/ * d3drm; TYPE_1__ IDirect3DRMLight_iface; } ;
typedef  int /*<<< orphan*/  IDirect3DRM ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  IDirect3DRM_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,struct d3drm_light**) ; 
 int /*<<< orphan*/  d3drm_light_vtbl ; 
 int /*<<< orphan*/  d3drm_object_init (int /*<<< orphan*/ *,char const*) ; 
 struct d3drm_light* heap_alloc_zero (int) ; 

HRESULT d3drm_light_create(struct d3drm_light **light, IDirect3DRM *d3drm)
{
    static const char classname[] = "Light";
    struct d3drm_light *object;

    TRACE("light %p.\n", light);

    if (!(object = heap_alloc_zero(sizeof(*object))))
        return E_OUTOFMEMORY;

    object->IDirect3DRMLight_iface.lpVtbl = &d3drm_light_vtbl;
    object->ref = 1;
    object->d3drm = d3drm;
    IDirect3DRM_AddRef(object->d3drm);

    d3drm_object_init(&object->obj, classname);

    *light = object;

    return S_OK;
}