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
struct wined3d_format {int* flags; scalar_t__ depth_size; scalar_t__ stencil_size; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int WINED3DFMT_FLAG_FLOAT ; 
 size_t WINED3D_GL_RES_TYPE_TEX_2D ; 

__attribute__((used)) static BOOL match_depth_stencil_format(const struct wined3d_format *existing,
        const struct wined3d_format *required)
{
    if (existing == required)
        return TRUE;
    if ((existing->flags[WINED3D_GL_RES_TYPE_TEX_2D] & WINED3DFMT_FLAG_FLOAT)
            != (required->flags[WINED3D_GL_RES_TYPE_TEX_2D] & WINED3DFMT_FLAG_FLOAT))
        return FALSE;
    if (existing->depth_size < required->depth_size)
        return FALSE;
    /* If stencil bits are used the exact amount is required - otherwise
     * wrapping won't work correctly. */
    if (required->stencil_size && required->stencil_size != existing->stencil_size)
        return FALSE;
    return TRUE;
}