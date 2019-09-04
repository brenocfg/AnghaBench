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
typedef  enum wined3d_decl_usage { ____Placeholder_wined3d_decl_usage } wined3d_decl_usage ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
#define  WINED3D_DECL_USAGE_BINORMAL 141 
#define  WINED3D_DECL_USAGE_BLEND_INDICES 140 
#define  WINED3D_DECL_USAGE_BLEND_WEIGHT 139 
#define  WINED3D_DECL_USAGE_COLOR 138 
#define  WINED3D_DECL_USAGE_DEPTH 137 
#define  WINED3D_DECL_USAGE_FOG 136 
#define  WINED3D_DECL_USAGE_NORMAL 135 
#define  WINED3D_DECL_USAGE_POSITION 134 
#define  WINED3D_DECL_USAGE_POSITIONT 133 
#define  WINED3D_DECL_USAGE_PSIZE 132 
#define  WINED3D_DECL_USAGE_SAMPLE 131 
#define  WINED3D_DECL_USAGE_TANGENT 130 
#define  WINED3D_DECL_USAGE_TESS_FACTOR 129 
#define  WINED3D_DECL_USAGE_TEXCOORD 128 

const char *debug_d3ddeclusage(enum wined3d_decl_usage usage)
{
    switch (usage)
    {
#define WINED3DDECLUSAGE_TO_STR(u) case u: return #u
        WINED3DDECLUSAGE_TO_STR(WINED3D_DECL_USAGE_POSITION);
        WINED3DDECLUSAGE_TO_STR(WINED3D_DECL_USAGE_BLEND_WEIGHT);
        WINED3DDECLUSAGE_TO_STR(WINED3D_DECL_USAGE_BLEND_INDICES);
        WINED3DDECLUSAGE_TO_STR(WINED3D_DECL_USAGE_NORMAL);
        WINED3DDECLUSAGE_TO_STR(WINED3D_DECL_USAGE_PSIZE);
        WINED3DDECLUSAGE_TO_STR(WINED3D_DECL_USAGE_TEXCOORD);
        WINED3DDECLUSAGE_TO_STR(WINED3D_DECL_USAGE_TANGENT);
        WINED3DDECLUSAGE_TO_STR(WINED3D_DECL_USAGE_BINORMAL);
        WINED3DDECLUSAGE_TO_STR(WINED3D_DECL_USAGE_TESS_FACTOR);
        WINED3DDECLUSAGE_TO_STR(WINED3D_DECL_USAGE_POSITIONT);
        WINED3DDECLUSAGE_TO_STR(WINED3D_DECL_USAGE_COLOR);
        WINED3DDECLUSAGE_TO_STR(WINED3D_DECL_USAGE_FOG);
        WINED3DDECLUSAGE_TO_STR(WINED3D_DECL_USAGE_DEPTH);
        WINED3DDECLUSAGE_TO_STR(WINED3D_DECL_USAGE_SAMPLE);
#undef WINED3DDECLUSAGE_TO_STR
        default:
            FIXME("Unrecognized %u declaration usage!\n", usage);
            return "unrecognized";
    }
}