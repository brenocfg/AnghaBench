#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  (* p_glLoadMatrixd ) (double const*) ;int /*<<< orphan*/  (* p_glMatrixMode ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ gl; } ;
struct wined3d_gl_info {TYPE_2__ gl_ops; } ;
struct wined3d_context {struct wined3d_gl_info* gl_info; } ;
typedef  double GLdouble ;

/* Variables and functions */
 int /*<<< orphan*/  GL_PROJECTION ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (double const*) ; 

__attribute__((used)) static void context_apply_blit_projection(const struct wined3d_context *context, unsigned int w, unsigned int h)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;
    const GLdouble projection[] =
    {
        2.0 / w,     0.0,  0.0, 0.0,
            0.0, 2.0 / h,  0.0, 0.0,
            0.0,     0.0,  2.0, 0.0,
           -1.0,    -1.0, -1.0, 1.0,
    };

    gl_info->gl_ops.gl.p_glMatrixMode(GL_PROJECTION);
    gl_info->gl_ops.gl.p_glLoadMatrixd(projection);
}