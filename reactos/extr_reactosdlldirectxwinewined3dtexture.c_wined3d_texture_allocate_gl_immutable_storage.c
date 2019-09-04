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
struct wined3d_texture {int target; int /*<<< orphan*/  level_count; int /*<<< orphan*/  layer_count; } ;
struct wined3d_gl_info {int dummy; } ;
typedef  int /*<<< orphan*/  GLsizei ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_FALSE ; 
#define  GL_TEXTURE_1D 133 
#define  GL_TEXTURE_1D_ARRAY 132 
#define  GL_TEXTURE_2D_ARRAY 131 
#define  GL_TEXTURE_2D_MULTISAMPLE 130 
#define  GL_TEXTURE_2D_MULTISAMPLE_ARRAY 129 
#define  GL_TEXTURE_3D 128 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  glTexStorage1D (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glTexStorage2D (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glTexStorage2DMultisample (int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glTexStorage3D (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glTexStorage3DMultisample (int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int wined3d_texture_get_gl_sample_count (struct wined3d_texture*) ; 
 int /*<<< orphan*/  wined3d_texture_get_level_depth (struct wined3d_texture*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_texture_get_level_pow2_height (struct wined3d_texture*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_texture_get_level_pow2_width (struct wined3d_texture*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wined3d_texture_allocate_gl_immutable_storage(struct wined3d_texture *texture,
        GLenum gl_internal_format, const struct wined3d_gl_info *gl_info)
{
    unsigned int samples = wined3d_texture_get_gl_sample_count(texture);
    GLsizei height = wined3d_texture_get_level_pow2_height(texture, 0);
    GLsizei width = wined3d_texture_get_level_pow2_width(texture, 0);

    switch (texture->target)
    {
        case GL_TEXTURE_3D:
            GL_EXTCALL(glTexStorage3D(texture->target, texture->level_count,
                    gl_internal_format, width, height, wined3d_texture_get_level_depth(texture, 0)));
            break;
        case GL_TEXTURE_2D_ARRAY:
            GL_EXTCALL(glTexStorage3D(texture->target, texture->level_count,
                    gl_internal_format, width, height, texture->layer_count));
            break;
        case GL_TEXTURE_2D_MULTISAMPLE:
            GL_EXTCALL(glTexStorage2DMultisample(texture->target, samples,
                    gl_internal_format, width, height, GL_FALSE));
            break;
        case GL_TEXTURE_2D_MULTISAMPLE_ARRAY:
            GL_EXTCALL(glTexStorage3DMultisample(texture->target, samples,
                    gl_internal_format, width, height, texture->layer_count, GL_FALSE));
            break;
        case GL_TEXTURE_1D_ARRAY:
            GL_EXTCALL(glTexStorage2D(texture->target, texture->level_count,
                    gl_internal_format, width, texture->layer_count));
            break;
        case GL_TEXTURE_1D:
            GL_EXTCALL(glTexStorage1D(texture->target, texture->level_count, gl_internal_format, width));
            break;
        default:
            GL_EXTCALL(glTexStorage2D(texture->target, texture->level_count,
                    gl_internal_format, width, height));
            break;
    }

    checkGLcall("allocate immutable storage");
}