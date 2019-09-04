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
struct wined3d_gl_info {int /*<<< orphan*/ * supported; } ;
struct wined3d_device {int /*<<< orphan*/ * shader_backend; TYPE_1__* adapter; } ;
struct wined3d_blitter {struct wined3d_blitter* next; int /*<<< orphan*/ * ops; } ;
struct wined3d_arbfp_blitter {struct wined3d_blitter blitter; scalar_t__ palette_texture; int /*<<< orphan*/  shaders; } ;
struct TYPE_2__ {struct wined3d_gl_info gl_info; } ;

/* Variables and functions */
 size_t ARB_FRAGMENT_PROGRAM ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  TRACE (char*,struct wined3d_arbfp_blitter*) ; 
 size_t WINED3D_GL_LEGACY_CONTEXT ; 
 int /*<<< orphan*/  arb_program_shader_backend ; 
 int /*<<< orphan*/  arbfp_blit_type_compare ; 
 int /*<<< orphan*/  arbfp_blitter_ops ; 
 int /*<<< orphan*/  glsl_shader_backend ; 
 struct wined3d_arbfp_blitter* heap_alloc (int) ; 
 int /*<<< orphan*/  wine_rb_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void wined3d_arbfp_blitter_create(struct wined3d_blitter **next, const struct wined3d_device *device)
{
    const struct wined3d_gl_info *gl_info = &device->adapter->gl_info;
    struct wined3d_arbfp_blitter *blitter;

    if (device->shader_backend != &arb_program_shader_backend
            && device->shader_backend != &glsl_shader_backend)
        return;

    if (!gl_info->supported[ARB_FRAGMENT_PROGRAM])
        return;

    if (!gl_info->supported[WINED3D_GL_LEGACY_CONTEXT])
        return;

    if (!(blitter = heap_alloc(sizeof(*blitter))))
    {
        ERR("Failed to allocate blitter.\n");
        return;
    }

    TRACE("Created blitter %p.\n", blitter);

    blitter->blitter.ops = &arbfp_blitter_ops;
    blitter->blitter.next = *next;
    wine_rb_init(&blitter->shaders, arbfp_blit_type_compare);
    blitter->palette_texture = 0;
    *next = &blitter->blitter;
}