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

/* Variables and functions */
 void* pglDebugMessageCallbackARB ; 
 void* pglDebugMessageControlARB ; 
 void* pglDebugMessageInsertARB ; 
 void* pwglChoosePixelFormatARB ; 
 void* pwglCreateContextAttribsARB ; 
 void* pwglCreatePbufferARB ; 
 void* pwglGetCurrentReadDCARB ; 
 void* pwglGetExtensionsStringARB ; 
 void* pwglGetPbufferDCARB ; 
 void* pwglGetPixelFormatAttribivARB ; 
 void* pwglGetSwapIntervalEXT ; 
 void* pwglMakeContextCurrentARB ; 
 void* pwglReleasePbufferDCARB ; 
 void* pwglSwapIntervalEXT ; 
 int /*<<< orphan*/  trace (char*,char*) ; 
 scalar_t__ wglGetProcAddress (char*) ; 

__attribute__((used)) static void init_functions(void)
{
#define GET_PROC(func) \
    p ## func = (void*)wglGetProcAddress(#func); \
    if(!p ## func) \
      trace("wglGetProcAddress(%s) failed\n", #func);

    /* WGL_ARB_create_context */
    GET_PROC(wglCreateContextAttribsARB);

    /* WGL_ARB_extensions_string */
    GET_PROC(wglGetExtensionsStringARB)

    /* WGL_ARB_make_current_read */
    GET_PROC(wglMakeContextCurrentARB);
    GET_PROC(wglGetCurrentReadDCARB);

    /* WGL_ARB_pixel_format */
    GET_PROC(wglChoosePixelFormatARB)
    GET_PROC(wglGetPixelFormatAttribivARB)

    /* WGL_ARB_pbuffer */
    GET_PROC(wglCreatePbufferARB)
    GET_PROC(wglGetPbufferDCARB)
    GET_PROC(wglReleasePbufferDCARB)

    /* WGL_EXT_swap_control */
    GET_PROC(wglSwapIntervalEXT)
    GET_PROC(wglGetSwapIntervalEXT)

    /* GL_ARB_debug_output */
    GET_PROC(glDebugMessageCallbackARB)
    GET_PROC(glDebugMessageControlARB)
    GET_PROC(glDebugMessageInsertARB)

#undef GET_PROC
}