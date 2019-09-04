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
struct d3drm_visual_array {int ref; unsigned int size; int /*<<< orphan*/ ** visuals; TYPE_1__ IDirect3DRMVisualArray_iface; } ;
typedef  int /*<<< orphan*/  IDirect3DRMVisual ;

/* Variables and functions */
 int /*<<< orphan*/  IDirect3DRMVisual_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d3drm_visual_array_vtbl ; 
 struct d3drm_visual_array* heap_alloc_zero (int) ; 
 int /*<<< orphan*/ ** heap_calloc (unsigned int,int) ; 
 int /*<<< orphan*/  heap_free (struct d3drm_visual_array*) ; 

__attribute__((used)) static struct d3drm_visual_array *d3drm_visual_array_create(unsigned int visual_count, IDirect3DRMVisual **visuals)
{
    struct d3drm_visual_array *array;
    unsigned int i;

    if (!(array = heap_alloc_zero(sizeof(*array))))
        return NULL;

    array->IDirect3DRMVisualArray_iface.lpVtbl = &d3drm_visual_array_vtbl;
    array->ref = 1;
    array->size = visual_count;

    if (visual_count)
    {
        if (!(array->visuals = heap_calloc(visual_count, sizeof(*array->visuals))))
        {
            heap_free(array);
            return NULL;
        }

        for (i = 0; i < visual_count; ++i)
        {
            array->visuals[i] = visuals[i];
            IDirect3DRMVisual_AddRef(array->visuals[i]);
        }
    }

    return array;
}