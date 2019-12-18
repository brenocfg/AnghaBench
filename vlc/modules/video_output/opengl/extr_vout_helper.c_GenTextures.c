#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int tex_count; int (* pf_allocate_textures ) (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ;TYPE_1__* vt; int /*<<< orphan*/  tex_target; } ;
typedef  TYPE_2__ opengl_tex_converter_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* DeleteTextures ) (unsigned int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* TexParameteri ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* TexEnvf ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* TexParameterf ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,double) ;int /*<<< orphan*/  (* BindTexture ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* GenTextures ) (unsigned int,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLsizei ;

/* Variables and functions */
 int /*<<< orphan*/  GL_CLAMP_TO_EDGE ; 
 int /*<<< orphan*/  GL_LINEAR ; 
 int /*<<< orphan*/  GL_MODULATE ; 
 int /*<<< orphan*/  GL_TEXTURE_ENV ; 
 int /*<<< orphan*/  GL_TEXTURE_ENV_MODE ; 
 int /*<<< orphan*/  GL_TEXTURE_MAG_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_MIN_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_PRIORITY ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_S ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_T ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub10 (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub9 (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
GenTextures(const opengl_tex_converter_t *tc,
            const GLsizei *tex_width, const GLsizei *tex_height,
            GLuint *textures)
{
    tc->vt->GenTextures(tc->tex_count, textures);

    for (unsigned i = 0; i < tc->tex_count; i++)
    {
        tc->vt->BindTexture(tc->tex_target, textures[i]);

#if !defined(USE_OPENGL_ES2)
        /* Set the texture parameters */
        tc->vt->TexParameterf(tc->tex_target, GL_TEXTURE_PRIORITY, 1.0);
        tc->vt->TexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
#endif

        tc->vt->TexParameteri(tc->tex_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        tc->vt->TexParameteri(tc->tex_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        tc->vt->TexParameteri(tc->tex_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        tc->vt->TexParameteri(tc->tex_target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }

    if (tc->pf_allocate_textures != NULL)
    {
        int ret = tc->pf_allocate_textures(tc, textures, tex_width, tex_height);
        if (ret != VLC_SUCCESS)
        {
            tc->vt->DeleteTextures(tc->tex_count, textures);
            memset(textures, 0, tc->tex_count * sizeof(GLuint));
            return ret;
        }
    }
    return VLC_SUCCESS;
}