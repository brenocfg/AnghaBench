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
struct d3dx_parameter {int dummy; } ;
struct d3dx9_base_effect {int dummy; } ;
typedef  size_t UINT ;
typedef  int /*<<< orphan*/ * D3DXHANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,struct d3dx_parameter*) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 size_t get_annotation_from_object (struct d3dx9_base_effect*,int /*<<< orphan*/ *,struct d3dx_parameter**) ; 
 int /*<<< orphan*/ * get_parameter_handle (struct d3dx_parameter*) ; 

__attribute__((used)) static D3DXHANDLE d3dx9_base_effect_get_annotation(struct d3dx9_base_effect *base,
        D3DXHANDLE object, UINT index)
{
    struct d3dx_parameter *annotations = NULL;
    UINT annotation_count = 0;

    annotation_count = get_annotation_from_object(base, object, &annotations);

    if (index < annotation_count)
    {
        TRACE("Returning parameter %p\n", &annotations[index]);
        return get_parameter_handle(&annotations[index]);
    }

    WARN("Annotation not found.\n");

    return NULL;
}