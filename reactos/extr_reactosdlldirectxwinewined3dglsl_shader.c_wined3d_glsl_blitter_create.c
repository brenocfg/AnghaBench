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
struct wined3d_blitter {struct wined3d_blitter* next; int /*<<< orphan*/ * ops; } ;
struct wined3d_glsl_blitter {struct wined3d_blitter blitter; scalar_t__ palette_texture; int /*<<< orphan*/  programs; int /*<<< orphan*/  string_buffers; } ;
struct wined3d_gl_info {int /*<<< orphan*/ * supported; } ;
struct wined3d_device {int /*<<< orphan*/ * shader_backend; TYPE_1__* adapter; } ;
struct TYPE_2__ {struct wined3d_gl_info gl_info; } ;

/* Variables and functions */
 size_t ARB_FRAGMENT_SHADER ; 
 size_t ARB_VERTEX_SHADER ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  TRACE (char*,struct wined3d_glsl_blitter*) ; 
 int /*<<< orphan*/  glsl_blitter_args_compare ; 
 int /*<<< orphan*/  glsl_blitter_ops ; 
 int /*<<< orphan*/  glsl_shader_backend ; 
 struct wined3d_glsl_blitter* heap_alloc (int) ; 
 int /*<<< orphan*/  string_buffer_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wine_rb_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct wined3d_blitter *wined3d_glsl_blitter_create(struct wined3d_blitter **next,
        const struct wined3d_device *device)
{
    const struct wined3d_gl_info *gl_info = &device->adapter->gl_info;
    struct wined3d_glsl_blitter *blitter;

    if (device->shader_backend != &glsl_shader_backend)
        return NULL;

    if (!gl_info->supported[ARB_VERTEX_SHADER] || !gl_info->supported[ARB_FRAGMENT_SHADER])
        return NULL;

    if (!(blitter = heap_alloc(sizeof(*blitter))))
    {
        ERR("Failed to allocate blitter.\n");
        return NULL;
    }

    TRACE("Created blitter %p.\n", blitter);

    blitter->blitter.ops = &glsl_blitter_ops;
    blitter->blitter.next = *next;
    string_buffer_list_init(&blitter->string_buffers);
    wine_rb_init(&blitter->programs, glsl_blitter_args_compare);
    blitter->palette_texture = 0;
    *next = &blitter->blitter;

    return *next;
}