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
struct wined3d_state {int dummy; } ;
struct wined3d_gl_info {int dummy; } ;
struct wined3d_context {struct wined3d_gl_info* gl_info; } ;
struct shader_none_priv {TYPE_2__* fragment_pipe; TYPE_1__* vertex_pipe; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* enable_extension ) (struct wined3d_gl_info const*,int) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* vp_enable ) (struct wined3d_gl_info const*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct wined3d_gl_info const*,int) ; 
 int /*<<< orphan*/  stub2 (struct wined3d_gl_info const*,int) ; 
 int /*<<< orphan*/  use_ps (struct wined3d_state const*) ; 
 int /*<<< orphan*/  use_vs (struct wined3d_state const*) ; 

__attribute__((used)) static void shader_none_select(void *shader_priv, struct wined3d_context *context,
        const struct wined3d_state *state)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;
    struct shader_none_priv *priv = shader_priv;

    priv->vertex_pipe->vp_enable(gl_info, !use_vs(state));
    priv->fragment_pipe->enable_extension(gl_info, !use_ps(state));
}