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
struct wined3d_gl_info {scalar_t__* supported; } ;
struct wined3d_context {int /*<<< orphan*/ * restore_pf_win; scalar_t__ restore_pf; struct wined3d_gl_info* gl_info; } ;
typedef  scalar_t__ HDC ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int DCX_CACHE ; 
 int DCX_USESTYLE ; 
 int /*<<< orphan*/  ERR (char*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 scalar_t__ GetDCEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ IsWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ *,scalar_t__) ; 
 size_t WGL_WINE_PIXEL_FORMAT_PASSTHROUGH ; 
 int /*<<< orphan*/  wglSetPixelFormatWINE (scalar_t__,scalar_t__) ; 

__attribute__((used)) static BOOL context_restore_pixel_format(struct wined3d_context *ctx)
{
    const struct wined3d_gl_info *gl_info = ctx->gl_info;
    BOOL ret = FALSE;

    if (ctx->restore_pf && IsWindow(ctx->restore_pf_win))
    {
        if (ctx->gl_info->supported[WGL_WINE_PIXEL_FORMAT_PASSTHROUGH])
        {
            HDC dc = GetDCEx(ctx->restore_pf_win, 0, DCX_USESTYLE | DCX_CACHE);
            if (dc)
            {
                if (!(ret = GL_EXTCALL(wglSetPixelFormatWINE(dc, ctx->restore_pf))))
                {
                    ERR("wglSetPixelFormatWINE failed to restore pixel format %d on window %p.\n",
                            ctx->restore_pf, ctx->restore_pf_win);
                }
                ReleaseDC(ctx->restore_pf_win, dc);
            }
        }
        else
        {
            ERR("can't restore pixel format %d on window %p\n", ctx->restore_pf, ctx->restore_pf_win);
        }
    }

    ctx->restore_pf = 0;
    ctx->restore_pf_win = NULL;
    return ret;
}