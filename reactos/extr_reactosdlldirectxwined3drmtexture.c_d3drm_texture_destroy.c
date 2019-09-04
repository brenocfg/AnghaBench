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
struct d3drm_texture {scalar_t__ surface; int /*<<< orphan*/  d3drm; scalar_t__ image; int /*<<< orphan*/  obj; int /*<<< orphan*/  IDirect3DRMTexture_iface; } ;
typedef  int /*<<< orphan*/  IDirect3DRMObject ;

/* Variables and functions */
 int /*<<< orphan*/  IDirect3DRM_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirectDrawSurface_Release (scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,struct d3drm_texture*) ; 
 int /*<<< orphan*/  d3drm_object_cleanup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_free (struct d3drm_texture*) ; 

__attribute__((used)) static void d3drm_texture_destroy(struct d3drm_texture *texture)
{
    TRACE("texture %p is being destroyed.\n", texture);

    d3drm_object_cleanup((IDirect3DRMObject*)&texture->IDirect3DRMTexture_iface, &texture->obj);
    if (texture->image || texture->surface)
        IDirect3DRM_Release(texture->d3drm);
    if (texture->surface)
        IDirectDrawSurface_Release(texture->surface);
    heap_free(texture);
}