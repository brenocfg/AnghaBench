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
#define  GL_INVALID_ENUM 135 
#define  GL_INVALID_FRAMEBUFFER_OPERATION 134 
#define  GL_INVALID_OPERATION 133 
#define  GL_INVALID_VALUE 132 
#define  GL_NO_ERROR 131 
#define  GL_OUT_OF_MEMORY 130 
#define  GL_STACK_OVERFLOW 129 
#define  GL_STACK_UNDERFLOW 128 

const char *debug_glerror(GLenum error) {
    switch(error) {
#define GLERROR_TO_STR(u) case u: return #u
        GLERROR_TO_STR(GL_NO_ERROR);
        GLERROR_TO_STR(GL_INVALID_ENUM);
        GLERROR_TO_STR(GL_INVALID_VALUE);
        GLERROR_TO_STR(GL_INVALID_OPERATION);
        GLERROR_TO_STR(GL_STACK_OVERFLOW);
        GLERROR_TO_STR(GL_STACK_UNDERFLOW);
        GLERROR_TO_STR(GL_OUT_OF_MEMORY);
        GLERROR_TO_STR(GL_INVALID_FRAMEBUFFER_OPERATION);
#undef GLERROR_TO_STR
        default:
            FIXME("Unrecognized GL error 0x%08x.\n", error);
            return "unrecognized";
    }
}