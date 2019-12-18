#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* vt; } ;
typedef  TYPE_2__ opengl_tex_converter_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* DeleteTextures ) (int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* GetTexLevelParameteriv ) (int,int /*<<< orphan*/ ,int,int*) ;int /*<<< orphan*/  (* TexImage2D ) (int,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* BindTexture ) (int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* GenTextures ) (int,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int GLint ;

/* Variables and functions */
#define  GL_BGRA 131 
#define  GL_LUMINANCE 130 
#define  GL_RED 129 
#define  GL_RG 128 
 int GL_TEXTURE_LUMINANCE_SIZE ; 
 int GL_TEXTURE_RED_SIZE ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (int,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  stub5 (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int GetTexFormatSize(opengl_tex_converter_t *tc, int target,
                            int tex_format, int tex_internal, int tex_type)
{
    if (!tc->vt->GetTexLevelParameteriv)
        return -1;

    GLint tex_param_size;
    int mul = 1;
    switch (tex_format)
    {
        case GL_BGRA:
            mul = 4;
            /* fall through */
        case GL_RED:
        case GL_RG:
            tex_param_size = GL_TEXTURE_RED_SIZE;
            break;
        case GL_LUMINANCE:
            tex_param_size = GL_TEXTURE_LUMINANCE_SIZE;
            break;
        default:
            return -1;
    }
    GLuint texture;

    tc->vt->GenTextures(1, &texture);
    tc->vt->BindTexture(target, texture);
    tc->vt->TexImage2D(target, 0, tex_internal, 64, 64, 0, tex_format, tex_type, NULL);
    GLint size = 0;
    tc->vt->GetTexLevelParameteriv(target, 0, tex_param_size, &size);

    tc->vt->DeleteTextures(1, &texture);
    return size > 0 ? size * mul : size;
}