#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct priv {int /*<<< orphan*/ * last_pic; int /*<<< orphan*/  gl_ctx; } ;
typedef  int /*<<< orphan*/  picture_t ;
struct TYPE_7__ {unsigned int tex_count; int /*<<< orphan*/  gl; TYPE_2__* texs; int /*<<< orphan*/  tex_target; TYPE_1__* vt; struct priv* priv; } ;
typedef  TYPE_3__ opengl_tex_converter_t ;
struct TYPE_6__ {int /*<<< orphan*/  type; int /*<<< orphan*/  format; int /*<<< orphan*/  internal; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* BindTexture ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* ActiveTexture ) (scalar_t__) ;} ;
typedef  int /*<<< orphan*/  IOSurfaceRef ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLsizei ;
typedef  int /*<<< orphan*/  CVPixelBufferRef ;
typedef  scalar_t__ CGLError ;

/* Variables and functions */
 int /*<<< orphan*/  CGLErrorString (scalar_t__) ; 
 scalar_t__ CGLTexImageIOSurface2D (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  CVPixelBufferGetIOSurface (int /*<<< orphan*/ ) ; 
 scalar_t__ GL_TEXTURE0 ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  cvpxpic_get_ref (int /*<<< orphan*/ *) ; 
 scalar_t__ kCGLNoError ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ ,char*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * picture_Hold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  picture_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tc_cvpx_update(const opengl_tex_converter_t *tc, GLuint *textures,
               const GLsizei *tex_width, const GLsizei *tex_height,
               picture_t *pic, const size_t *plane_offset)
{
    (void) plane_offset;
    struct priv *priv = tc->priv;

    CVPixelBufferRef pixelBuffer = cvpxpic_get_ref(pic);

    IOSurfaceRef surface = CVPixelBufferGetIOSurface(pixelBuffer);

    for (unsigned i = 0; i < tc->tex_count; ++i)
    {
        tc->vt->ActiveTexture(GL_TEXTURE0 + i);
        tc->vt->BindTexture(tc->tex_target, textures[i]);

        CGLError err =
            CGLTexImageIOSurface2D(priv->gl_ctx, tc->tex_target,
                                   tc->texs[i].internal,
                                   tex_width[i], tex_height[i],
                                   tc->texs[i].format,
                                   tc->texs[i].type,
                                   surface, i);
        if (err != kCGLNoError)
        {
            msg_Err(tc->gl, "CGLTexImageIOSurface2D error: %u: %s", i,
                    CGLErrorString(err));
            return VLC_EGENERIC;
        }
    }

    if (priv->last_pic != pic)
    {
        if (priv->last_pic != NULL)
            picture_Release(priv->last_pic);
        priv->last_pic = picture_Hold(pic);
    }

    return VLC_SUCCESS;
}