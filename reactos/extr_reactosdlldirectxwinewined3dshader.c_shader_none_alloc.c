#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wined3d_vertex_pipe_ops {int /*<<< orphan*/  (* vp_free ) (struct wined3d_device*) ;void* (* vp_alloc ) (int /*<<< orphan*/ *,struct shader_none_priv*) ;} ;
struct wined3d_device {struct shader_none_priv* shader_priv; void* fragment_priv; void* vertex_priv; TYPE_1__* adapter; } ;
struct shader_none_priv {int ffp_proj_control; struct fragment_pipeline const* fragment_pipe; struct wined3d_vertex_pipe_ops const* vertex_pipe; } ;
struct fragment_pipeline {int /*<<< orphan*/  (* get_caps ) (int /*<<< orphan*/ *,struct fragment_caps*) ;void* (* alloc_private ) (int /*<<< orphan*/ *,struct shader_none_priv*) ;} ;
struct fragment_caps {int wined3d_caps; } ;
struct TYPE_2__ {int /*<<< orphan*/  gl_info; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int WINED3D_FRAGMENT_CAP_PROJ_CONTROL ; 
 int /*<<< orphan*/  WINED3D_OK ; 
 struct shader_none_priv* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (struct shader_none_priv*) ; 
 int /*<<< orphan*/  none_shader_backend ; 
 void* stub1 (int /*<<< orphan*/ *,struct shader_none_priv*) ; 
 void* stub2 (int /*<<< orphan*/ *,struct shader_none_priv*) ; 
 int /*<<< orphan*/  stub3 (struct wined3d_device*) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,struct fragment_caps*) ; 

__attribute__((used)) static HRESULT shader_none_alloc(struct wined3d_device *device, const struct wined3d_vertex_pipe_ops *vertex_pipe,
        const struct fragment_pipeline *fragment_pipe)
{
    struct fragment_caps fragment_caps;
    void *vertex_priv, *fragment_priv;
    struct shader_none_priv *priv;

    if (!(priv = heap_alloc(sizeof(*priv))))
        return E_OUTOFMEMORY;

    if (!(vertex_priv = vertex_pipe->vp_alloc(&none_shader_backend, priv)))
    {
        ERR("Failed to initialize vertex pipe.\n");
        heap_free(priv);
        return E_FAIL;
    }

    if (!(fragment_priv = fragment_pipe->alloc_private(&none_shader_backend, priv)))
    {
        ERR("Failed to initialize fragment pipe.\n");
        vertex_pipe->vp_free(device);
        heap_free(priv);
        return E_FAIL;
    }

    priv->vertex_pipe = vertex_pipe;
    priv->fragment_pipe = fragment_pipe;
    fragment_pipe->get_caps(&device->adapter->gl_info, &fragment_caps);
    priv->ffp_proj_control = fragment_caps.wined3d_caps & WINED3D_FRAGMENT_CAP_PROJ_CONTROL;

    device->vertex_priv = vertex_priv;
    device->fragment_priv = fragment_priv;
    device->shader_priv = priv;

    return WINED3D_OK;
}