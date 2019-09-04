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
struct wined3d_gl_info {int dummy; } ;
typedef  int GLuint ;
typedef  int GLenum ;
typedef  int DWORD ;

/* Variables and functions */
 int ARG_UNUSED ; 
 int ATIFS_CONST_STAGE (unsigned int) ; 
 int ATIFS_CONST_TFACTOR ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int GL_ALPHA ; 
 int GL_COMP_BIT_ATI ; 
 int GL_NONE ; 
 int GL_PRIMARY_COLOR ; 
 int GL_REG_0_ATI ; 
 int GL_SECONDARY_INTERPOLATOR_ATI ; 
 int GL_ZERO ; 
 int WINED3DTA_ALPHAREPLICATE ; 
 int WINED3DTA_COMPLEMENT ; 
#define  WINED3DTA_CONSTANT 134 
#define  WINED3DTA_CURRENT 133 
#define  WINED3DTA_DIFFUSE 132 
 int WINED3DTA_SELECTMASK ; 
#define  WINED3DTA_SPECULAR 131 
#define  WINED3DTA_TEMP 130 
#define  WINED3DTA_TEXTURE 129 
#define  WINED3DTA_TFACTOR 128 

__attribute__((used)) static GLuint register_for_arg(DWORD arg, const struct wined3d_gl_info *gl_info,
        unsigned int stage, GLuint *mod, GLuint *rep, GLuint tmparg)
{
    GLenum ret;

    if(mod) *mod = GL_NONE;
    if(arg == ARG_UNUSED)
    {
        if (rep) *rep = GL_NONE;
        return -1; /* This is the marker for unused registers */
    }

    switch(arg & WINED3DTA_SELECTMASK) {
        case WINED3DTA_DIFFUSE:
            ret = GL_PRIMARY_COLOR;
            break;

        case WINED3DTA_CURRENT:
            /* Note that using GL_REG_0_ATI for the passed on register is safe because
             * texture0 is read at stage0, so in the worst case it is read in the
             * instruction writing to reg0. Afterwards texture0 is not used any longer.
             * If we're reading from current
             */
            ret = stage ? GL_REG_0_ATI : GL_PRIMARY_COLOR;
            break;

        case WINED3DTA_TEXTURE:
            ret = GL_REG_0_ATI + stage;
            break;

        case WINED3DTA_TFACTOR:
            ret = ATIFS_CONST_TFACTOR;
            break;

        case WINED3DTA_SPECULAR:
            ret = GL_SECONDARY_INTERPOLATOR_ATI;
            break;

        case WINED3DTA_TEMP:
            ret = tmparg;
            break;

        case WINED3DTA_CONSTANT:
            ret = ATIFS_CONST_STAGE(stage);
            break;

        default:
            FIXME("Unknown source argument %d\n", arg);
            ret = GL_ZERO;
    }

    if(arg & WINED3DTA_COMPLEMENT) {
        if(mod) *mod |= GL_COMP_BIT_ATI;
    }
    if(arg & WINED3DTA_ALPHAREPLICATE) {
        if(rep) *rep = GL_ALPHA;
    } else {
        if(rep) *rep = GL_NONE;
    }
    return ret;
}