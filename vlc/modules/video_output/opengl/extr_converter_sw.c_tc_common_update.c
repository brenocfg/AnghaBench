#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* p; } ;
typedef  TYPE_3__ picture_t ;
struct TYPE_11__ {unsigned int tex_count; int /*<<< orphan*/  tex_target; TYPE_1__* vt; } ;
typedef  TYPE_4__ opengl_tex_converter_t ;
struct TYPE_9__ {int /*<<< orphan*/  i_visible_pitch; int /*<<< orphan*/  i_pitch; int /*<<< orphan*/ * p_pixels; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* BindTexture ) (int /*<<< orphan*/ ,scalar_t__) ;int /*<<< orphan*/  (* ActiveTexture ) (scalar_t__) ;} ;
typedef  scalar_t__ GLuint ;
typedef  int /*<<< orphan*/  GLsizei ;

/* Variables and functions */
 scalar_t__ GL_TEXTURE0 ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,scalar_t__) ; 
 int upload_plane (TYPE_4__ const*,unsigned int,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*) ; 

__attribute__((used)) static int
tc_common_update(const opengl_tex_converter_t *tc, GLuint *textures,
                 const GLsizei *tex_width, const GLsizei *tex_height,
                 picture_t *pic, const size_t *plane_offset)
{
    int ret = VLC_SUCCESS;
    for (unsigned i = 0; i < tc->tex_count && ret == VLC_SUCCESS; i++)
    {
        assert(textures[i] != 0);
        tc->vt->ActiveTexture(GL_TEXTURE0 + i);
        tc->vt->BindTexture(tc->tex_target, textures[i]);
        const void *pixels = plane_offset != NULL ?
                             &pic->p[i].p_pixels[plane_offset[i]] :
                             pic->p[i].p_pixels;

        ret = upload_plane(tc, i, tex_width[i], tex_height[i],
                           pic->p[i].i_pitch, pic->p[i].i_visible_pitch, pixels);
    }
    return ret;
}