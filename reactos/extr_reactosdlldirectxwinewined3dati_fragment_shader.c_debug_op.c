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
typedef  int GLuint ;

/* Variables and functions */
#define  GL_ADD_ATI 138 
#define  GL_CND0_ATI 137 
#define  GL_CND_ATI 136 
#define  GL_DOT2_ADD_ATI 135 
#define  GL_DOT3_ATI 134 
#define  GL_DOT4_ATI 133 
#define  GL_LERP_ATI 132 
#define  GL_MAD_ATI 131 
#define  GL_MOV_ATI 130 
#define  GL_MUL_ATI 129 
#define  GL_SUB_ATI 128 

__attribute__((used)) static const char *debug_op(GLuint op) {
    switch(op) {
        case GL_MOV_ATI:                return "GL_MOV_ATI";
        case GL_ADD_ATI:                return "GL_ADD_ATI";
        case GL_MUL_ATI:                return "GL_MUL_ATI";
        case GL_SUB_ATI:                return "GL_SUB_ATI";
        case GL_DOT3_ATI:               return "GL_DOT3_ATI";
        case GL_DOT4_ATI:               return "GL_DOT4_ATI";
        case GL_MAD_ATI:                return "GL_MAD_ATI";
        case GL_LERP_ATI:               return "GL_LERP_ATI";
        case GL_CND_ATI:                return "GL_CND_ATI";
        case GL_CND0_ATI:               return "GL_CND0_ATI";
        case GL_DOT2_ADD_ATI:           return "GL_DOT2_ADD_ATI";
        default:                        return "unexpected op";
    }
}