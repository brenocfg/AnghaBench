#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  (* DrawElements ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* UniformMatrix4fv ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* VertexAttribPointer ) (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* EnableVertexAttribArray ) (int) ;int /*<<< orphan*/  (* BindBuffer ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* BindTexture ) (int /*<<< orphan*/ ,scalar_t__) ;int /*<<< orphan*/  (* ActiveTexture ) (scalar_t__) ;} ;
struct TYPE_17__ {scalar_t__* texture; int /*<<< orphan*/  nb_indices; TYPE_6__ vt; int /*<<< orphan*/  index_buffer_object; int /*<<< orphan*/  vertex_buffer_object; int /*<<< orphan*/ * texture_buffer_object; TYPE_2__* prgm; int /*<<< orphan*/  tex_height; int /*<<< orphan*/  tex_width; } ;
typedef  TYPE_7__ vout_display_opengl_t ;
struct TYPE_15__ {int /*<<< orphan*/  ZoomMatrix; int /*<<< orphan*/  ViewMatrix; int /*<<< orphan*/  ProjectionMatrix; int /*<<< orphan*/  OrientationMatrix; } ;
struct TYPE_14__ {int /*<<< orphan*/  ZoomMatrix; int /*<<< orphan*/  ViewMatrix; int /*<<< orphan*/  ProjectionMatrix; int /*<<< orphan*/  OrientationMatrix; } ;
struct TYPE_13__ {int* MultiTexCoord; int VertexPosition; } ;
struct prgm {TYPE_5__ var; TYPE_4__ uloc; TYPE_3__ aloc; TYPE_8__* tc; } ;
struct TYPE_18__ {int /*<<< orphan*/  tex_target; int /*<<< orphan*/  (* pf_prepare_shader ) (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float) ;} ;
typedef  TYPE_8__ opengl_tex_converter_t ;
struct TYPE_12__ {TYPE_1__* tc; } ;
struct TYPE_11__ {unsigned int tex_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_ELEMENT_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_FLOAT ; 
 scalar_t__ GL_TEXTURE0 ; 
 int /*<<< orphan*/  GL_TRIANGLES ; 
 int /*<<< orphan*/  GL_UNSIGNED_SHORT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  stub10 (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub12 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub13 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub14 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (scalar_t__) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int) ; 
 int /*<<< orphan*/  stub6 (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (int) ; 

__attribute__((used)) static void DrawWithShaders(vout_display_opengl_t *vgl, struct prgm *prgm)
{
    opengl_tex_converter_t *tc = prgm->tc;
    tc->pf_prepare_shader(tc, vgl->tex_width, vgl->tex_height, 1.0f);

    for (unsigned j = 0; j < vgl->prgm->tc->tex_count; j++) {
        assert(vgl->texture[j] != 0);
        vgl->vt.ActiveTexture(GL_TEXTURE0+j);
        vgl->vt.BindTexture(tc->tex_target, vgl->texture[j]);

        vgl->vt.BindBuffer(GL_ARRAY_BUFFER, vgl->texture_buffer_object[j]);

        assert(prgm->aloc.MultiTexCoord[j] != -1);
        vgl->vt.EnableVertexAttribArray(prgm->aloc.MultiTexCoord[j]);
        vgl->vt.VertexAttribPointer(prgm->aloc.MultiTexCoord[j], 2, GL_FLOAT,
                                     0, 0, 0);
    }

    vgl->vt.BindBuffer(GL_ARRAY_BUFFER, vgl->vertex_buffer_object);
    vgl->vt.BindBuffer(GL_ELEMENT_ARRAY_BUFFER, vgl->index_buffer_object);
    vgl->vt.EnableVertexAttribArray(prgm->aloc.VertexPosition);
    vgl->vt.VertexAttribPointer(prgm->aloc.VertexPosition, 3, GL_FLOAT, 0, 0, 0);

    vgl->vt.UniformMatrix4fv(prgm->uloc.OrientationMatrix, 1, GL_FALSE,
                             prgm->var.OrientationMatrix);
    vgl->vt.UniformMatrix4fv(prgm->uloc.ProjectionMatrix, 1, GL_FALSE,
                             prgm->var.ProjectionMatrix);
    vgl->vt.UniformMatrix4fv(prgm->uloc.ViewMatrix, 1, GL_FALSE,
                             prgm->var.ViewMatrix);
    vgl->vt.UniformMatrix4fv(prgm->uloc.ZoomMatrix, 1, GL_FALSE,
                             prgm->var.ZoomMatrix);

    vgl->vt.DrawElements(GL_TRIANGLES, vgl->nb_indices, GL_UNSIGNED_SHORT, 0);
}