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
struct TYPE_2__ {scalar_t__ multisample_type; int /*<<< orphan*/  multisample_quality; struct wined3d_format* format; } ;
struct wined3d_texture {TYPE_1__ resource; } ;
struct wined3d_format {unsigned int multisample_types; } ;

/* Variables and functions */
 int CHAR_BIT ; 
 scalar_t__ WINED3D_MULTISAMPLE_NON_MASKABLE ; 

__attribute__((used)) static unsigned int wined3d_texture_get_gl_sample_count(const struct wined3d_texture *texture)
{
    const struct wined3d_format *format = texture->resource.format;

    /* TODO: NVIDIA expose their Coverage Sample Anti-Aliasing (CSAA)
     * feature through type == MULTISAMPLE_XX and quality != 0. This could
     * be mapped to GL_NV_framebuffer_multisample_coverage.
     *
     * AMD have a similar feature called Enhanced Quality Anti-Aliasing
     * (EQAA), but it does not have an equivalent OpenGL extension. */

    /* We advertise as many WINED3D_MULTISAMPLE_NON_MASKABLE quality
     * levels as the count of advertised multisample types for the texture
     * format. */
    if (texture->resource.multisample_type == WINED3D_MULTISAMPLE_NON_MASKABLE)
    {
        unsigned int i, count = 0;

        for (i = 0; i < sizeof(format->multisample_types) * CHAR_BIT; ++i)
        {
            if (format->multisample_types & 1u << i)
            {
                if (texture->resource.multisample_quality == count++)
                    break;
            }
        }
        return i + 1;
    }

    return texture->resource.multisample_type;
}