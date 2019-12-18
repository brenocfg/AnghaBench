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
struct priv {int /*<<< orphan*/ * transform_mtx; int /*<<< orphan*/  awh; } ;
struct TYPE_9__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ picture_t ;
struct TYPE_10__ {int /*<<< orphan*/  b_locked; } ;
typedef  TYPE_3__ picture_sys_t ;
struct TYPE_11__ {int /*<<< orphan*/  tex_target; TYPE_1__* vt; struct priv* priv; } ;
typedef  TYPE_4__ opengl_tex_converter_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* BindTexture ) (int /*<<< orphan*/ ,scalar_t__) ;int /*<<< orphan*/  (* ActiveTexture ) (int /*<<< orphan*/ ) ;} ;
typedef  scalar_t__ GLuint ;
typedef  int /*<<< orphan*/  GLsizei ;

/* Variables and functions */
 int /*<<< orphan*/  AndroidOpaquePicture_Release (TYPE_3__*,int) ; 
 int /*<<< orphan*/  GL_TEXTURE0 ; 
 int SurfaceTexture_waitAndUpdateTexImage (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
tc_anop_update(const opengl_tex_converter_t *tc, GLuint *textures,
               const GLsizei *tex_width, const GLsizei *tex_height,
               picture_t *pic, const size_t *plane_offset)
{
    picture_sys_t *p_sys = pic->p_sys;
    (void) tex_width; (void) tex_height; (void) plane_offset;
    assert(textures[0] != 0);

    if (plane_offset != NULL)
        return VLC_EGENERIC;

    if (!p_sys->b_locked)
        return VLC_SUCCESS;

    struct priv *priv = tc->priv;

    AndroidOpaquePicture_Release(pic->p_sys, true);

    if (SurfaceTexture_waitAndUpdateTexImage(priv->awh, &priv->transform_mtx)
        != VLC_SUCCESS)
    {
        priv->transform_mtx = NULL;
        return VLC_EGENERIC;
    }

    tc->vt->ActiveTexture(GL_TEXTURE0);
    tc->vt->BindTexture(tc->tex_target, textures[0]);

    return VLC_SUCCESS;
}