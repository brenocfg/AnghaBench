#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wined3d_vec3 {float x; float y; float z; } ;
struct wined3d_texture {unsigned int level_count; } ;
struct wined3d_rect_f {float t; float l; float r; float b; } ;
struct wined3d_blt_info {int bind_target; struct wined3d_vec3* texcoords; } ;
struct TYPE_4__ {float left; float top; float right; float bottom; } ;
typedef  TYPE_1__ RECT ;
typedef  float GLsizei ;
typedef  int GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
#define  GL_TEXTURE_2D 135 
 void* GL_TEXTURE_CUBE_MAP_ARB ; 
#define  GL_TEXTURE_CUBE_MAP_NEGATIVE_X 134 
#define  GL_TEXTURE_CUBE_MAP_NEGATIVE_Y 133 
#define  GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 132 
#define  GL_TEXTURE_CUBE_MAP_POSITIVE_X 131 
#define  GL_TEXTURE_CUBE_MAP_POSITIVE_Y 130 
#define  GL_TEXTURE_CUBE_MAP_POSITIVE_Z 129 
#define  GL_TEXTURE_RECTANGLE_ARB 128 
 int /*<<< orphan*/  cube_coords_float (TYPE_1__ const*,float,float,struct wined3d_rect_f*) ; 
 float wined3d_texture_get_level_pow2_height (struct wined3d_texture const*,unsigned int) ; 
 float wined3d_texture_get_level_pow2_width (struct wined3d_texture const*,unsigned int) ; 
 int wined3d_texture_get_sub_resource_target (struct wined3d_texture const*,unsigned int) ; 

void texture2d_get_blt_info(const struct wined3d_texture *texture,
        unsigned int sub_resource_idx, const RECT *rect, struct wined3d_blt_info *info)
{
    struct wined3d_vec3 *coords = info->texcoords;
    struct wined3d_rect_f f;
    unsigned int level;
    GLenum target;
    GLsizei w, h;

    level = sub_resource_idx % texture->level_count;
    w = wined3d_texture_get_level_pow2_width(texture, level);
    h = wined3d_texture_get_level_pow2_height(texture, level);
    target = wined3d_texture_get_sub_resource_target(texture, sub_resource_idx);

    switch (target)
    {
        default:
            FIXME("Unsupported texture target %#x.\n", target);
            /* Fall back to GL_TEXTURE_2D */
        case GL_TEXTURE_2D:
            info->bind_target = GL_TEXTURE_2D;
            coords[0].x = (float)rect->left / w;
            coords[0].y = (float)rect->top / h;
            coords[0].z = 0.0f;

            coords[1].x = (float)rect->right / w;
            coords[1].y = (float)rect->top / h;
            coords[1].z = 0.0f;

            coords[2].x = (float)rect->left / w;
            coords[2].y = (float)rect->bottom / h;
            coords[2].z = 0.0f;

            coords[3].x = (float)rect->right / w;
            coords[3].y = (float)rect->bottom / h;
            coords[3].z = 0.0f;
            break;

        case GL_TEXTURE_RECTANGLE_ARB:
            info->bind_target = GL_TEXTURE_RECTANGLE_ARB;
            coords[0].x = rect->left;  coords[0].y = rect->top;    coords[0].z = 0.0f;
            coords[1].x = rect->right; coords[1].y = rect->top;    coords[1].z = 0.0f;
            coords[2].x = rect->left;  coords[2].y = rect->bottom; coords[2].z = 0.0f;
            coords[3].x = rect->right; coords[3].y = rect->bottom; coords[3].z = 0.0f;
            break;

        case GL_TEXTURE_CUBE_MAP_POSITIVE_X:
            info->bind_target = GL_TEXTURE_CUBE_MAP_ARB;
            cube_coords_float(rect, w, h, &f);

            coords[0].x =  1.0f;   coords[0].y = -f.t;   coords[0].z = -f.l;
            coords[1].x =  1.0f;   coords[1].y = -f.t;   coords[1].z = -f.r;
            coords[2].x =  1.0f;   coords[2].y = -f.b;   coords[2].z = -f.l;
            coords[3].x =  1.0f;   coords[3].y = -f.b;   coords[3].z = -f.r;
            break;

        case GL_TEXTURE_CUBE_MAP_NEGATIVE_X:
            info->bind_target = GL_TEXTURE_CUBE_MAP_ARB;
            cube_coords_float(rect, w, h, &f);

            coords[0].x = -1.0f;   coords[0].y = -f.t;   coords[0].z = f.l;
            coords[1].x = -1.0f;   coords[1].y = -f.t;   coords[1].z = f.r;
            coords[2].x = -1.0f;   coords[2].y = -f.b;   coords[2].z = f.l;
            coords[3].x = -1.0f;   coords[3].y = -f.b;   coords[3].z = f.r;
            break;

        case GL_TEXTURE_CUBE_MAP_POSITIVE_Y:
            info->bind_target = GL_TEXTURE_CUBE_MAP_ARB;
            cube_coords_float(rect, w, h, &f);

            coords[0].x = f.l;   coords[0].y =  1.0f;   coords[0].z = f.t;
            coords[1].x = f.r;   coords[1].y =  1.0f;   coords[1].z = f.t;
            coords[2].x = f.l;   coords[2].y =  1.0f;   coords[2].z = f.b;
            coords[3].x = f.r;   coords[3].y =  1.0f;   coords[3].z = f.b;
            break;

        case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y:
            info->bind_target = GL_TEXTURE_CUBE_MAP_ARB;
            cube_coords_float(rect, w, h, &f);

            coords[0].x = f.l;   coords[0].y = -1.0f;   coords[0].z = -f.t;
            coords[1].x = f.r;   coords[1].y = -1.0f;   coords[1].z = -f.t;
            coords[2].x = f.l;   coords[2].y = -1.0f;   coords[2].z = -f.b;
            coords[3].x = f.r;   coords[3].y = -1.0f;   coords[3].z = -f.b;
            break;

        case GL_TEXTURE_CUBE_MAP_POSITIVE_Z:
            info->bind_target = GL_TEXTURE_CUBE_MAP_ARB;
            cube_coords_float(rect, w, h, &f);

            coords[0].x = f.l;   coords[0].y = -f.t;   coords[0].z =  1.0f;
            coords[1].x = f.r;   coords[1].y = -f.t;   coords[1].z =  1.0f;
            coords[2].x = f.l;   coords[2].y = -f.b;   coords[2].z =  1.0f;
            coords[3].x = f.r;   coords[3].y = -f.b;   coords[3].z =  1.0f;
            break;

        case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z:
            info->bind_target = GL_TEXTURE_CUBE_MAP_ARB;
            cube_coords_float(rect, w, h, &f);

            coords[0].x = -f.l;   coords[0].y = -f.t;   coords[0].z = -1.0f;
            coords[1].x = -f.r;   coords[1].y = -f.t;   coords[1].z = -1.0f;
            coords[2].x = -f.l;   coords[2].y = -f.b;   coords[2].z = -1.0f;
            coords[3].x = -f.r;   coords[3].y = -f.b;   coords[3].z = -1.0f;
            break;
    }
}