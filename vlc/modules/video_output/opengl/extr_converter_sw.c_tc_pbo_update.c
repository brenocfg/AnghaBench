#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t display_idx; TYPE_5__** display_pics; } ;
struct priv {TYPE_1__ pbo; } ;
struct TYPE_14__ {int i_planes; TYPE_2__* p; TYPE_6__* p_sys; } ;
typedef  TYPE_5__ picture_t ;
struct TYPE_15__ {int /*<<< orphan*/ * buffers; } ;
typedef  TYPE_6__ picture_sys_t ;
struct TYPE_16__ {TYPE_4__* vt; TYPE_3__* texs; int /*<<< orphan*/  tex_target; struct priv* priv; } ;
typedef  TYPE_7__ opengl_tex_converter_t ;
struct TYPE_13__ {int /*<<< orphan*/  (* BindBuffer ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* TexSubImage2D ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* PixelStorei ) (int /*<<< orphan*/ ,int const) ;int /*<<< orphan*/  (* BindTexture ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* ActiveTexture ) (scalar_t__) ;int /*<<< orphan*/  (* BufferSubData ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  type; int /*<<< orphan*/  format; } ;
struct TYPE_11__ {int i_lines; int i_pitch; int i_visible_pitch; int /*<<< orphan*/ * p_pixels; } ;
typedef  int /*<<< orphan*/  GLvoid ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int GLsizeiptr ;
typedef  int GLsizei ;

/* Variables and functions */
 int /*<<< orphan*/  GL_PIXEL_UNPACK_BUFFER ; 
 scalar_t__ GL_TEXTURE0 ; 
 int /*<<< orphan*/  GL_UNPACK_ROW_LENGTH ; 
 int PBO_DISPLAY_COUNT ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stub3 (scalar_t__) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tc_pbo_update(const opengl_tex_converter_t *tc, GLuint *textures,
              const GLsizei *tex_width, const GLsizei *tex_height,
              picture_t *pic, const size_t *plane_offset)
{
    (void) plane_offset; assert(plane_offset == NULL);
    struct priv *priv = tc->priv;

    picture_t *display_pic = priv->pbo.display_pics[priv->pbo.display_idx];
    picture_sys_t *p_sys = display_pic->p_sys;
    priv->pbo.display_idx = (priv->pbo.display_idx + 1) % PBO_DISPLAY_COUNT;

    for (int i = 0; i < pic->i_planes; i++)
    {
        GLsizeiptr size = pic->p[i].i_lines * pic->p[i].i_pitch;
        const GLvoid *data = pic->p[i].p_pixels;
        tc->vt->BindBuffer(GL_PIXEL_UNPACK_BUFFER,
                           p_sys->buffers[i]);
        tc->vt->BufferSubData(GL_PIXEL_UNPACK_BUFFER, 0, size, data);

        tc->vt->ActiveTexture(GL_TEXTURE0 + i);
        tc->vt->BindTexture(tc->tex_target, textures[i]);

        tc->vt->PixelStorei(GL_UNPACK_ROW_LENGTH, pic->p[i].i_pitch
            * tex_width[i] / (pic->p[i].i_visible_pitch ? pic->p[i].i_visible_pitch : 1));

        tc->vt->TexSubImage2D(tc->tex_target, 0, 0, 0, tex_width[i], tex_height[i],
                              tc->texs[i].format, tc->texs[i].type, NULL);
    }

    /* turn off pbo */
    tc->vt->BindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

    return VLC_SUCCESS;
}