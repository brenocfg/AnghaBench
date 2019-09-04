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
typedef  int /*<<< orphan*/  HGLRC ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  context_set_current (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wglMakeCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void context_restore_gl_context(const struct wined3d_gl_info *gl_info, HDC dc, HGLRC gl_ctx)
{
    if (!wglMakeCurrent(dc, gl_ctx))
    {
        ERR("Failed to restore GL context %p on device context %p, last error %#x.\n",
                gl_ctx, dc, GetLastError());
        context_set_current(NULL);
    }
}