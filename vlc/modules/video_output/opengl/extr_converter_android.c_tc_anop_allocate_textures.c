#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct priv {int stex_attached; int /*<<< orphan*/  awh; } ;
struct TYPE_3__ {int /*<<< orphan*/  gl; struct priv* priv; } ;
typedef  TYPE_1__ opengl_tex_converter_t ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLsizei ;

/* Variables and functions */
 scalar_t__ SurfaceTexture_attachToGLContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
tc_anop_allocate_textures(const opengl_tex_converter_t *tc, GLuint *textures,
                          const GLsizei *tex_width, const GLsizei *tex_height)
{
    (void) tex_width; (void) tex_height;
    struct priv *priv = tc->priv;
    assert(textures[0] != 0);
    if (SurfaceTexture_attachToGLContext(priv->awh, textures[0]) != 0)
    {
        msg_Err(tc->gl, "SurfaceTexture_attachToGLContext failed");
        return VLC_EGENERIC;
    }
    priv->stex_attached = true;
    return VLC_SUCCESS;
}