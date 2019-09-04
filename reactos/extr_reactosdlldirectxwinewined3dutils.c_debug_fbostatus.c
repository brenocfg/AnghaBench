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
 int /*<<< orphan*/  FIXME (char*,int) ; 
#define  GL_FRAMEBUFFER_COMPLETE 139 
#define  GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT 138 
#define  GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT 137 
#define  GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER 136 
#define  GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT 135 
#define  GL_FRAMEBUFFER_INCOMPLETE_LAYER_COUNT_ARB 134 
#define  GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS 133 
#define  GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT 132 
#define  GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE 131 
#define  GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER 130 
#define  GL_FRAMEBUFFER_UNDEFINED 129 
#define  GL_FRAMEBUFFER_UNSUPPORTED 128 

const char *debug_fbostatus(GLenum status) {
    switch(status) {
#define FBOSTATUS_TO_STR(u) case u: return #u
        FBOSTATUS_TO_STR(GL_FRAMEBUFFER_COMPLETE);
        FBOSTATUS_TO_STR(GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT);
        FBOSTATUS_TO_STR(GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT);
        FBOSTATUS_TO_STR(GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT);
        FBOSTATUS_TO_STR(GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT);
        FBOSTATUS_TO_STR(GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER);
        FBOSTATUS_TO_STR(GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER);
        FBOSTATUS_TO_STR(GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE);
        FBOSTATUS_TO_STR(GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS);
        FBOSTATUS_TO_STR(GL_FRAMEBUFFER_INCOMPLETE_LAYER_COUNT_ARB);
        FBOSTATUS_TO_STR(GL_FRAMEBUFFER_UNSUPPORTED);
        FBOSTATUS_TO_STR(GL_FRAMEBUFFER_UNDEFINED);
#undef FBOSTATUS_TO_STR
        default:
            FIXME("Unrecognized FBO status 0x%08x.\n", status);
            return "unrecognized";
    }
}