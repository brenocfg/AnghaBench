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
struct TYPE_4__ {float r; float g; float b; } ;
struct TYPE_3__ {int /*<<< orphan*/ * lpVtbl; } ;
struct d3drm_material {int ref; int /*<<< orphan*/  obj; TYPE_2__ specular; int /*<<< orphan*/ * d3drm; TYPE_1__ IDirect3DRMMaterial2_iface; } ;
typedef  int /*<<< orphan*/  IDirect3DRM ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  IDirect3DRM_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,struct d3drm_material**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d3drm_material_vtbl ; 
 int /*<<< orphan*/  d3drm_object_init (int /*<<< orphan*/ *,char const*) ; 
 struct d3drm_material* heap_alloc_zero (int) ; 

HRESULT d3drm_material_create(struct d3drm_material **material, IDirect3DRM *d3drm)
{
    static const char classname[] = "Material";
    struct d3drm_material *object;

    TRACE("material %p, d3drm %p.\n", material, d3drm);

    if (!(object = heap_alloc_zero(sizeof(*object))))
        return E_OUTOFMEMORY;

    object->IDirect3DRMMaterial2_iface.lpVtbl = &d3drm_material_vtbl;
    object->ref = 1;
    object->d3drm = d3drm;
    IDirect3DRM_AddRef(object->d3drm);

    object->specular.r = 1.0f;
    object->specular.g = 1.0f;
    object->specular.b = 1.0f;

    d3drm_object_init(&object->obj, classname);

    *material = object;

    return S_OK;
}