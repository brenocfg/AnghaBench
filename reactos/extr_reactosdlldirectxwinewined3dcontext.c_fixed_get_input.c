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
typedef  scalar_t__ BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ WINED3DDP_MAXTEXCOORD ; 
 scalar_t__ WINED3D_DECL_USAGE_BLEND_INDICES ; 
 scalar_t__ WINED3D_DECL_USAGE_BLEND_WEIGHT ; 
 scalar_t__ WINED3D_DECL_USAGE_COLOR ; 
 scalar_t__ WINED3D_DECL_USAGE_NORMAL ; 
 scalar_t__ WINED3D_DECL_USAGE_POSITION ; 
 scalar_t__ WINED3D_DECL_USAGE_POSITIONT ; 
 scalar_t__ WINED3D_DECL_USAGE_PSIZE ; 
 scalar_t__ WINED3D_DECL_USAGE_TEXCOORD ; 
 unsigned int WINED3D_FFP_BLENDINDICES ; 
 unsigned int WINED3D_FFP_BLENDWEIGHT ; 
 unsigned int WINED3D_FFP_DIFFUSE ; 
 unsigned int WINED3D_FFP_NORMAL ; 
 unsigned int WINED3D_FFP_POSITION ; 
 unsigned int WINED3D_FFP_PSIZE ; 
 unsigned int WINED3D_FFP_SPECULAR ; 
 scalar_t__ WINED3D_FFP_TEXCOORD0 ; 
 int /*<<< orphan*/  debug_d3ddeclusage (scalar_t__) ; 

__attribute__((used)) static BOOL fixed_get_input(BYTE usage, BYTE usage_idx, unsigned int *regnum)
{
    if ((usage == WINED3D_DECL_USAGE_POSITION || usage == WINED3D_DECL_USAGE_POSITIONT) && !usage_idx)
        *regnum = WINED3D_FFP_POSITION;
    else if (usage == WINED3D_DECL_USAGE_BLEND_WEIGHT && !usage_idx)
        *regnum = WINED3D_FFP_BLENDWEIGHT;
    else if (usage == WINED3D_DECL_USAGE_BLEND_INDICES && !usage_idx)
        *regnum = WINED3D_FFP_BLENDINDICES;
    else if (usage == WINED3D_DECL_USAGE_NORMAL && !usage_idx)
        *regnum = WINED3D_FFP_NORMAL;
    else if (usage == WINED3D_DECL_USAGE_PSIZE && !usage_idx)
        *regnum = WINED3D_FFP_PSIZE;
    else if (usage == WINED3D_DECL_USAGE_COLOR && !usage_idx)
        *regnum = WINED3D_FFP_DIFFUSE;
    else if (usage == WINED3D_DECL_USAGE_COLOR && usage_idx == 1)
        *regnum = WINED3D_FFP_SPECULAR;
    else if (usage == WINED3D_DECL_USAGE_TEXCOORD && usage_idx < WINED3DDP_MAXTEXCOORD)
        *regnum = WINED3D_FFP_TEXCOORD0 + usage_idx;
    else
    {
        WARN("Unsupported input stream [usage=%s, usage_idx=%u].\n", debug_d3ddeclusage(usage), usage_idx);
        *regnum = ~0u;
        return FALSE;
    }

    return TRUE;
}