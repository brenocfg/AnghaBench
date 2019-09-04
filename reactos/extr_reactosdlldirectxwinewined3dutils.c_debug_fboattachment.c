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
typedef  int GLenum ;

/* Variables and functions */
#define  GL_COLOR_ATTACHMENT0 145 
#define  GL_COLOR_ATTACHMENT1 144 
#define  GL_COLOR_ATTACHMENT10 143 
#define  GL_COLOR_ATTACHMENT11 142 
#define  GL_COLOR_ATTACHMENT12 141 
#define  GL_COLOR_ATTACHMENT13 140 
#define  GL_COLOR_ATTACHMENT14 139 
#define  GL_COLOR_ATTACHMENT15 138 
#define  GL_COLOR_ATTACHMENT2 137 
#define  GL_COLOR_ATTACHMENT3 136 
#define  GL_COLOR_ATTACHMENT4 135 
#define  GL_COLOR_ATTACHMENT5 134 
#define  GL_COLOR_ATTACHMENT6 133 
#define  GL_COLOR_ATTACHMENT7 132 
#define  GL_COLOR_ATTACHMENT8 131 
#define  GL_COLOR_ATTACHMENT9 130 
#define  GL_DEPTH_ATTACHMENT 129 
#define  GL_STENCIL_ATTACHMENT 128 
 char const* wine_dbg_sprintf (char*,int) ; 

const char *debug_fboattachment(GLenum attachment)
{
    switch(attachment)
    {
#define WINED3D_TO_STR(x) case x: return #x
        WINED3D_TO_STR(GL_COLOR_ATTACHMENT0);
        WINED3D_TO_STR(GL_COLOR_ATTACHMENT1);
        WINED3D_TO_STR(GL_COLOR_ATTACHMENT2);
        WINED3D_TO_STR(GL_COLOR_ATTACHMENT3);
        WINED3D_TO_STR(GL_COLOR_ATTACHMENT4);
        WINED3D_TO_STR(GL_COLOR_ATTACHMENT5);
        WINED3D_TO_STR(GL_COLOR_ATTACHMENT6);
        WINED3D_TO_STR(GL_COLOR_ATTACHMENT7);
        WINED3D_TO_STR(GL_COLOR_ATTACHMENT8);
        WINED3D_TO_STR(GL_COLOR_ATTACHMENT9);
        WINED3D_TO_STR(GL_COLOR_ATTACHMENT10);
        WINED3D_TO_STR(GL_COLOR_ATTACHMENT11);
        WINED3D_TO_STR(GL_COLOR_ATTACHMENT12);
        WINED3D_TO_STR(GL_COLOR_ATTACHMENT13);
        WINED3D_TO_STR(GL_COLOR_ATTACHMENT14);
        WINED3D_TO_STR(GL_COLOR_ATTACHMENT15);
        WINED3D_TO_STR(GL_DEPTH_ATTACHMENT);
        WINED3D_TO_STR(GL_STENCIL_ATTACHMENT);
#undef WINED3D_TO_STR
        default:
            return wine_dbg_sprintf("Unknown FBO attachment %#x", attachment);
    }
}