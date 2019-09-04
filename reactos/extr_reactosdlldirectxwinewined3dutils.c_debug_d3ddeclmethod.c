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
typedef  enum wined3d_decl_method { ____Placeholder_wined3d_decl_method } wined3d_decl_method ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
#define  WINED3D_DECL_METHOD_CROSS_UV 134 
#define  WINED3D_DECL_METHOD_DEFAULT 133 
#define  WINED3D_DECL_METHOD_LOOKUP 132 
#define  WINED3D_DECL_METHOD_LOOKUP_PRESAMPLED 131 
#define  WINED3D_DECL_METHOD_PARTIAL_U 130 
#define  WINED3D_DECL_METHOD_PARTIAL_V 129 
#define  WINED3D_DECL_METHOD_UV 128 

const char *debug_d3ddeclmethod(enum wined3d_decl_method method)
{
    switch (method)
    {
#define WINED3DDECLMETHOD_TO_STR(u) case u: return #u
        WINED3DDECLMETHOD_TO_STR(WINED3D_DECL_METHOD_DEFAULT);
        WINED3DDECLMETHOD_TO_STR(WINED3D_DECL_METHOD_PARTIAL_U);
        WINED3DDECLMETHOD_TO_STR(WINED3D_DECL_METHOD_PARTIAL_V);
        WINED3DDECLMETHOD_TO_STR(WINED3D_DECL_METHOD_CROSS_UV);
        WINED3DDECLMETHOD_TO_STR(WINED3D_DECL_METHOD_UV);
        WINED3DDECLMETHOD_TO_STR(WINED3D_DECL_METHOD_LOOKUP);
        WINED3DDECLMETHOD_TO_STR(WINED3D_DECL_METHOD_LOOKUP_PRESAMPLED);
#undef WINED3DDECLMETHOD_TO_STR
        default:
            FIXME("Unrecognized declaration method %#x.\n", method);
            return "unrecognized";
    }
}