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
struct TYPE_2__ {int /*<<< orphan*/  glGenerateMipmap; } ;
struct wined3d_gl_info {unsigned int format_count; struct wined3d_format* formats; TYPE_1__ fbo_ops; } ;
struct wined3d_format {int* flags; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int*) ; 
 int WINED3DFMT_FLAG_FILTERING ; 
 int WINED3DFMT_FLAG_GEN_MIPMAP ; 
 int WINED3DFMT_FLAG_RENDERTARGET ; 

__attribute__((used)) static void init_format_gen_mipmap_info(struct wined3d_gl_info *gl_info)
{
    unsigned int i, j;

    if (!gl_info->fbo_ops.glGenerateMipmap)
        return;

    for (i = 0; i < gl_info->format_count; ++i)
    {
        struct wined3d_format *format = &gl_info->formats[i];

        for (j = 0; j < ARRAY_SIZE(format->flags); ++j)
            if (!(~format->flags[j] & (WINED3DFMT_FLAG_RENDERTARGET | WINED3DFMT_FLAG_FILTERING)))
                format->flags[j] |= WINED3DFMT_FLAG_GEN_MIPMAP;
    }
}