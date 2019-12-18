#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_19__ ;
typedef  struct TYPE_22__   TYPE_12__ ;
typedef  struct TYPE_21__   TYPE_11__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
struct TYPE_27__ {int /*<<< orphan*/  (* Disable ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* DrawArrays ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* UniformMatrix4fv ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* VertexAttribPointer ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* EnableVertexAttribArray ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* BufferData ) (int /*<<< orphan*/ ,int,double const*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* BindBuffer ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* BindTexture ) (int /*<<< orphan*/ ,scalar_t__) ;int /*<<< orphan*/  (* ActiveTexture ) (scalar_t__) ;int /*<<< orphan*/  (* GenBuffers ) (int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* DeleteBuffers ) (int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* BlendFunc ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* Enable ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* UseProgram ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* Clear ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_28__ {float i_x_offset; float i_y_offset; float i_visible_width; float i_visible_height; } ;
struct TYPE_32__ {float* tex_width; float* tex_height; int region_count; int subpicture_buffer_object_count; int /*<<< orphan*/  gl; TYPE_4__ vt; int /*<<< orphan*/ * subpicture_buffer_object; TYPE_12__* region; struct prgm* sub_prgm; TYPE_19__* prgm; TYPE_5__ last_source; } ;
typedef  TYPE_9__ vout_display_opengl_t ;
struct TYPE_20__ {float i_x_offset; float i_y_offset; float i_visible_width; float i_visible_height; } ;
typedef  TYPE_10__ video_format_t ;
typedef  int /*<<< orphan*/  vertexCoord ;
typedef  int /*<<< orphan*/  textureCoord ;
struct TYPE_26__ {int /*<<< orphan*/  ZoomMatrix; int /*<<< orphan*/  ViewMatrix; int /*<<< orphan*/  ProjectionMatrix; int /*<<< orphan*/  OrientationMatrix; } ;
struct TYPE_25__ {int /*<<< orphan*/  ZoomMatrix; int /*<<< orphan*/  ViewMatrix; int /*<<< orphan*/  ProjectionMatrix; int /*<<< orphan*/  OrientationMatrix; } ;
struct TYPE_24__ {int /*<<< orphan*/  VertexPosition; int /*<<< orphan*/ * MultiTexCoord; } ;
struct prgm {TYPE_3__ var; TYPE_2__ uloc; TYPE_1__ aloc; TYPE_11__* tc; int /*<<< orphan*/  id; } ;
struct TYPE_21__ {unsigned int tex_count; int /*<<< orphan*/  (* pf_prepare_shader ) (TYPE_11__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  tex_target; TYPE_8__* texs; } ;
typedef  TYPE_11__ opengl_tex_converter_t ;
struct TYPE_22__ {double const left; double const top; double const bottom; double const right; double tex_height; double tex_width; scalar_t__ texture; int /*<<< orphan*/  alpha; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_12__ gl_region_t ;
struct TYPE_30__ {float den; scalar_t__ num; } ;
struct TYPE_29__ {float den; scalar_t__ num; } ;
struct TYPE_31__ {TYPE_7__ h; TYPE_6__ w; } ;
struct TYPE_23__ {TYPE_11__* tc; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  double GLfloat ;

/* Variables and functions */
 int /*<<< orphan*/  DrawWithShaders (TYPE_9__*,TYPE_19__*) ; 
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_ASSERT_NOERROR () ; 
 int /*<<< orphan*/  GL_BLEND ; 
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_FLOAT ; 
 int /*<<< orphan*/  GL_ONE_MINUS_SRC_ALPHA ; 
 int /*<<< orphan*/  GL_SRC_ALPHA ; 
 int /*<<< orphan*/  GL_STATIC_DRAW ; 
 scalar_t__ GL_TEXTURE0 ; 
 int /*<<< orphan*/  GL_TRIANGLE_STRIP ; 
 int PICTURE_PLANE_MAX ; 
 int SetupCoords (TYPE_9__*,float*,float*,float*,float*) ; 
 int /*<<< orphan*/  TextureCropForStereo (TYPE_9__*,float*,float*,float*,float*) ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * realloc_or_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (TYPE_11__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub12 (int /*<<< orphan*/ ,int,double const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub13 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub14 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub16 (int /*<<< orphan*/ ,int,double const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub17 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub18 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub19 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub20 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub21 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub22 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub23 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub24 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub7 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub8 (scalar_t__) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vlc_gl_Swap (int /*<<< orphan*/ ) ; 

int vout_display_opengl_Display(vout_display_opengl_t *vgl,
                                const video_format_t *source)
{
    GL_ASSERT_NOERROR();

    /* Why drawing here and not in Render()? Because this way, the
       OpenGL providers can call vout_display_opengl_Display to force redraw.
       Currently, the OS X provider uses it to get a smooth window resizing */
    vgl->vt.Clear(GL_COLOR_BUFFER_BIT);

    vgl->vt.UseProgram(vgl->prgm->id);

    if (source->i_x_offset != vgl->last_source.i_x_offset
     || source->i_y_offset != vgl->last_source.i_y_offset
     || source->i_visible_width != vgl->last_source.i_visible_width
     || source->i_visible_height != vgl->last_source.i_visible_height)
    {
        float left[PICTURE_PLANE_MAX];
        float top[PICTURE_PLANE_MAX];
        float right[PICTURE_PLANE_MAX];
        float bottom[PICTURE_PLANE_MAX];
        const opengl_tex_converter_t *tc = vgl->prgm->tc;
        for (unsigned j = 0; j < tc->tex_count; j++)
        {
            float scale_w = (float)tc->texs[j].w.num / tc->texs[j].w.den
                          / vgl->tex_width[j];
            float scale_h = (float)tc->texs[j].h.num / tc->texs[j].h.den
                          / vgl->tex_height[j];

            /* Warning: if NPOT is not supported a larger texture is
               allocated. This will cause right and bottom coordinates to
               land on the edge of two texels with the texels to the
               right/bottom uninitialized by the call to
               glTexSubImage2D. This might cause a green line to appear on
               the right/bottom of the display.
               There are two possible solutions:
               - Manually mirror the edges of the texture.
               - Add a "-1" when computing right and bottom, however the
               last row/column might not be displayed at all.
            */
            left[j]   = (source->i_x_offset +                       0 ) * scale_w;
            top[j]    = (source->i_y_offset +                       0 ) * scale_h;
            right[j]  = (source->i_x_offset + source->i_visible_width ) * scale_w;
            bottom[j] = (source->i_y_offset + source->i_visible_height) * scale_h;
        }

        TextureCropForStereo(vgl, left, top, right, bottom);
        int ret = SetupCoords(vgl, left, top, right, bottom);
        if (ret != VLC_SUCCESS)
            return ret;

        vgl->last_source.i_x_offset = source->i_x_offset;
        vgl->last_source.i_y_offset = source->i_y_offset;
        vgl->last_source.i_visible_width = source->i_visible_width;
        vgl->last_source.i_visible_height = source->i_visible_height;
    }
    DrawWithShaders(vgl, vgl->prgm);

    /* Draw the subpictures */
    // Change the program for overlays
    struct prgm *prgm = vgl->sub_prgm;
    GLuint program = prgm->id;
    opengl_tex_converter_t *tc = prgm->tc;
    vgl->vt.UseProgram(program);

    vgl->vt.Enable(GL_BLEND);
    vgl->vt.BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /* We need two buffer objects for each region: for vertex and texture coordinates. */
    if (2 * vgl->region_count > vgl->subpicture_buffer_object_count) {
        if (vgl->subpicture_buffer_object_count > 0)
            vgl->vt.DeleteBuffers(vgl->subpicture_buffer_object_count,
                                  vgl->subpicture_buffer_object);
        vgl->subpicture_buffer_object_count = 0;

        int new_count = 2 * vgl->region_count;
        vgl->subpicture_buffer_object = realloc_or_free(vgl->subpicture_buffer_object, new_count * sizeof(GLuint));
        if (!vgl->subpicture_buffer_object)
            return VLC_ENOMEM;

        vgl->subpicture_buffer_object_count = new_count;
        vgl->vt.GenBuffers(vgl->subpicture_buffer_object_count,
                           vgl->subpicture_buffer_object);
    }

    vgl->vt.ActiveTexture(GL_TEXTURE0 + 0);
    for (int i = 0; i < vgl->region_count; i++) {
        gl_region_t *glr = &vgl->region[i];
        const GLfloat vertexCoord[] = {
            glr->left,  glr->top,
            glr->left,  glr->bottom,
            glr->right, glr->top,
            glr->right, glr->bottom,
        };
        const GLfloat textureCoord[] = {
            0.0, 0.0,
            0.0, glr->tex_height,
            glr->tex_width, 0.0,
            glr->tex_width, glr->tex_height,
        };

        assert(glr->texture != 0);
        vgl->vt.BindTexture(tc->tex_target, glr->texture);

        tc->pf_prepare_shader(tc, &glr->width, &glr->height, glr->alpha);

        vgl->vt.BindBuffer(GL_ARRAY_BUFFER, vgl->subpicture_buffer_object[2 * i]);
        vgl->vt.BufferData(GL_ARRAY_BUFFER, sizeof(textureCoord), textureCoord, GL_STATIC_DRAW);
        vgl->vt.EnableVertexAttribArray(prgm->aloc.MultiTexCoord[0]);
        vgl->vt.VertexAttribPointer(prgm->aloc.MultiTexCoord[0], 2, GL_FLOAT,
                                    0, 0, 0);

        vgl->vt.BindBuffer(GL_ARRAY_BUFFER, vgl->subpicture_buffer_object[2 * i + 1]);
        vgl->vt.BufferData(GL_ARRAY_BUFFER, sizeof(vertexCoord), vertexCoord, GL_STATIC_DRAW);
        vgl->vt.EnableVertexAttribArray(prgm->aloc.VertexPosition);
        vgl->vt.VertexAttribPointer(prgm->aloc.VertexPosition, 2, GL_FLOAT,
                                    0, 0, 0);

        vgl->vt.UniformMatrix4fv(prgm->uloc.OrientationMatrix, 1, GL_FALSE,
                                 prgm->var.OrientationMatrix);
        vgl->vt.UniformMatrix4fv(prgm->uloc.ProjectionMatrix, 1, GL_FALSE,
                                 prgm->var.ProjectionMatrix);
        vgl->vt.UniformMatrix4fv(prgm->uloc.ViewMatrix, 1, GL_FALSE,
                                 prgm->var.ViewMatrix);
        vgl->vt.UniformMatrix4fv(prgm->uloc.ZoomMatrix, 1, GL_FALSE,
                                 prgm->var.ZoomMatrix);

        vgl->vt.DrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
    vgl->vt.Disable(GL_BLEND);

    /* Display */
    vlc_gl_Swap(vgl->gl);

    GL_ASSERT_NOERROR();

    return VLC_SUCCESS;
}