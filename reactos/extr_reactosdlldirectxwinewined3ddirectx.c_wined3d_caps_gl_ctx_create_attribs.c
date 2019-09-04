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
struct wined3d_gl_info {int /*<<< orphan*/ * p_wglCreateContextAttribsARB; } ;
struct wined3d_caps_gl_ctx {int /*<<< orphan*/  gl_ctx; int /*<<< orphan*/  dc; } ;
typedef  int /*<<< orphan*/  HGLRC ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  context_create_wgl_attribs (struct wined3d_gl_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wglDeleteContext (int /*<<< orphan*/ ) ; 
 scalar_t__ wglGetProcAddress (char*) ; 
 int /*<<< orphan*/  wglMakeCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL wined3d_caps_gl_ctx_create_attribs(struct wined3d_caps_gl_ctx *caps_gl_ctx,
        struct wined3d_gl_info *gl_info)
{
    HGLRC new_ctx;

    if (!(gl_info->p_wglCreateContextAttribsARB = (void *)wglGetProcAddress("wglCreateContextAttribsARB")))
        return TRUE;

    if (!(new_ctx = context_create_wgl_attribs(gl_info, caps_gl_ctx->dc, NULL)))
    {
        gl_info->p_wglCreateContextAttribsARB = NULL;
        return FALSE;
    }

    if (!wglMakeCurrent(caps_gl_ctx->dc, new_ctx))
    {
        ERR("Failed to make new context current, last error %#x.\n", GetLastError());
        if (!wglDeleteContext(new_ctx))
            ERR("Failed to delete new context, last error %#x.\n", GetLastError());
        gl_info->p_wglCreateContextAttribsARB = NULL;
        return TRUE;
    }

    if (!wglDeleteContext(caps_gl_ctx->gl_ctx))
        ERR("Failed to delete old context, last error %#x.\n", GetLastError());
    caps_gl_ctx->gl_ctx = new_ctx;

    return TRUE;
}