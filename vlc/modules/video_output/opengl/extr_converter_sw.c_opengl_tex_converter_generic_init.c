#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_fourcc_t ;
typedef  int /*<<< orphan*/  video_color_space_t ;
struct priv {int has_unpack_subimage; } ;
struct TYPE_9__ {scalar_t__ i_chroma; int i_rmask; int i_gmask; int i_bmask; int /*<<< orphan*/  space; } ;
struct TYPE_8__ {scalar_t__ fshader; int /*<<< orphan*/  gl; int /*<<< orphan*/  pf_update; TYPE_1__* vt; int /*<<< orphan*/  glexts; int /*<<< orphan*/  is_gles; int /*<<< orphan*/  pf_allocate_textures; struct priv* priv; TYPE_3__ fmt; } ;
typedef  TYPE_2__ opengl_tex_converter_t ;
struct TYPE_7__ {unsigned char* (* GetString ) (int /*<<< orphan*/ ) ;scalar_t__ BufferSubData; scalar_t__ BufferData; int /*<<< orphan*/  (* DeleteShader ) (scalar_t__) ;int /*<<< orphan*/  (* GetIntegerv ) (int /*<<< orphan*/ ,int*) ;} ;
typedef  scalar_t__ GLuint ;
typedef  int GLint ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_SPACE_UNDEF ; 
 int /*<<< orphan*/  GL_MAX_TEXTURE_IMAGE_UNITS ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_VERSION ; 
 scalar_t__ VLC_CODEC_RGB32 ; 
#define  VLC_CODEC_XYZ12 128 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 scalar_t__ VLC_SUCCESS ; 
 struct priv* calloc (int,int) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ opengl_fragment_shader_init (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__ const,int /*<<< orphan*/ ) ; 
 scalar_t__ pbo_pics_alloc (TYPE_2__*) ; 
 scalar_t__ strverscmp (char const*,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (scalar_t__) ; 
 unsigned char* stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tc_common_allocate_textures ; 
 int /*<<< orphan*/  tc_common_update ; 
 int /*<<< orphan*/  tc_pbo_update ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_format_FixRgb (TYPE_3__*) ; 
 scalar_t__* vlc_fourcc_GetRGBFallback (scalar_t__) ; 
 scalar_t__* vlc_fourcc_GetYUVFallback (scalar_t__) ; 
 scalar_t__ vlc_fourcc_IsYUV (scalar_t__) ; 
 scalar_t__ vlc_gl_StrHasToken (int /*<<< orphan*/ ,char*) ; 

int
opengl_tex_converter_generic_init(opengl_tex_converter_t *tc, bool allow_dr)
{
    GLuint fragment_shader = 0;
    video_color_space_t space;
    const vlc_fourcc_t *list;

    if (vlc_fourcc_IsYUV(tc->fmt.i_chroma))
    {
        GLint max_texture_units = 0;
        tc->vt->GetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &max_texture_units);
        if (max_texture_units < 3)
            return VLC_EGENERIC;

        list = vlc_fourcc_GetYUVFallback(tc->fmt.i_chroma);
        space = tc->fmt.space;
    }
    else if (tc->fmt.i_chroma == VLC_CODEC_XYZ12)
    {
        static const vlc_fourcc_t xyz12_list[] = { VLC_CODEC_XYZ12, 0 };
        list = xyz12_list;
        space = COLOR_SPACE_UNDEF;
    }
    else
    {
        list = vlc_fourcc_GetRGBFallback(tc->fmt.i_chroma);
        space = COLOR_SPACE_UNDEF;
    }

    while (*list)
    {
        fragment_shader =
            opengl_fragment_shader_init(tc, GL_TEXTURE_2D, *list, space);
        if (fragment_shader != 0)
        {
            tc->fmt.i_chroma = *list;

            if (tc->fmt.i_chroma == VLC_CODEC_RGB32)
            {
#if defined(WORDS_BIGENDIAN)
                tc->fmt.i_rmask  = 0xff000000;
                tc->fmt.i_gmask  = 0x00ff0000;
                tc->fmt.i_bmask  = 0x0000ff00;
#else
                tc->fmt.i_rmask  = 0x000000ff;
                tc->fmt.i_gmask  = 0x0000ff00;
                tc->fmt.i_bmask  = 0x00ff0000;
#endif
                video_format_FixRgb(&tc->fmt);
            }
            break;
        }
        list++;
    }
    if (fragment_shader == 0)
        return VLC_EGENERIC;

    struct priv *priv = tc->priv = calloc(1, sizeof(struct priv));
    if (unlikely(priv == NULL))
    {
        tc->vt->DeleteShader(fragment_shader);
        return VLC_ENOMEM;
    }

    tc->pf_update            = tc_common_update;
    tc->pf_allocate_textures = tc_common_allocate_textures;

    /* OpenGL or OpenGL ES2 with GL_EXT_unpack_subimage ext */
    priv->has_unpack_subimage =
        !tc->is_gles || vlc_gl_StrHasToken(tc->glexts, "GL_EXT_unpack_subimage");

    if (allow_dr && priv->has_unpack_subimage)
    {
        /* Ensure we do direct rendering / PBO with OpenGL 3.0 or higher. */
        const unsigned char *ogl_version = tc->vt->GetString(GL_VERSION);
        const bool glver_ok = strverscmp((const char *)ogl_version, "3.0") >= 0;

        const bool has_pbo = glver_ok &&
            (vlc_gl_StrHasToken(tc->glexts, "GL_ARB_pixel_buffer_object") ||
             vlc_gl_StrHasToken(tc->glexts, "GL_EXT_pixel_buffer_object"));

        const bool supports_pbo = has_pbo && tc->vt->BufferData
            && tc->vt->BufferSubData;
        if (supports_pbo && pbo_pics_alloc(tc) == VLC_SUCCESS)
        {
            tc->pf_update  = tc_pbo_update;
            msg_Dbg(tc->gl, "PBO support enabled");
        }
    }

    tc->fshader = fragment_shader;

    return VLC_SUCCESS;
}