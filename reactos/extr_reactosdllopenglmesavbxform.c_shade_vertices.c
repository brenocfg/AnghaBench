#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct vertex_buffer {size_t Start; size_t Count; int /*<<< orphan*/ * Bindex; int /*<<< orphan*/ * Normal; int /*<<< orphan*/ * Eye; int /*<<< orphan*/ * Findex; int /*<<< orphan*/  MonoMaterial; int /*<<< orphan*/ ** Bcolor; int /*<<< orphan*/ ** Fcolor; scalar_t__ MonoNormal; } ;
struct TYPE_11__ {scalar_t__ TwoSide; } ;
struct TYPE_12__ {TYPE_2__ Model; scalar_t__ Fast; } ;
struct TYPE_13__ {TYPE_3__ Light; TYPE_1__* Visual; struct vertex_buffer* VB; } ;
struct TYPE_10__ {scalar_t__ RGBAflag; } ;
typedef  size_t GLuint ;
typedef  int /*<<< orphan*/  GLubyte ;
typedef  TYPE_4__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  COPY_4V (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl_color_shade_vertices (TYPE_4__*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  gl_color_shade_vertices_fast (TYPE_4__*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  gl_index_shade_vertices (TYPE_4__*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_material (TYPE_4__*,size_t) ; 

__attribute__((used)) static void shade_vertices( GLcontext *ctx )
{
   struct vertex_buffer *VB = ctx->VB;

   if (ctx->Visual->RGBAflag) {
      if (!VB->MonoMaterial) {
         /* Material may change with each vertex */
         GLuint i;
         for (i=VB->Start; i<VB->Count; i++) {
            update_material( ctx, i );
            gl_color_shade_vertices( ctx, 0, 1, &VB->Eye[i],
                                     &VB->Normal[i], &VB->Fcolor[i]);
            if (ctx->Light.Model.TwoSide) {
               gl_color_shade_vertices( ctx, 1, 1, &VB->Eye[i],
                                        &VB->Normal[i], &VB->Bcolor[i]);
            }
         }
         /* Need this in case a glColor/glMaterial is called after the
          * last vertex between glBegin/glEnd.
          */
         update_material( ctx, VB->Count );
      }
      else {
         if (ctx->Light.Fast) {
            if (VB->MonoNormal) {
               /* call optimized shader */
               GLubyte color[1][4];
               GLuint i;
               gl_color_shade_vertices_fast( ctx, 0,  /* front side */
                                             1,
                                             VB->Normal + VB->Start,
                                             color );
               for (i=VB->Start; i<VB->Count; i++) {
                  COPY_4V( VB->Fcolor[i], color[0] );
               }
               if (ctx->Light.Model.TwoSide) {
                  gl_color_shade_vertices_fast( ctx, 1,  /* back side */
                                                1,
                                                VB->Normal + VB->Start,
                                                color );
                  for (i=VB->Start; i<VB->Count; i++) {
                     COPY_4V( VB->Bcolor[i], color[0] );
                  }
               }

            }
            else {
               /* call optimized shader */
               gl_color_shade_vertices_fast( ctx, 0,  /* front side */
                                             VB->Count - VB->Start,
                                             VB->Normal + VB->Start,
                                             VB->Fcolor + VB->Start );
               if (ctx->Light.Model.TwoSide) {
                  gl_color_shade_vertices_fast( ctx, 1,  /* back side */
                                                VB->Count - VB->Start,
                                                VB->Normal + VB->Start,
                                                VB->Bcolor + VB->Start );
               }
            }
         }
         else {
            /* call slower, full-featured shader */
            gl_color_shade_vertices( ctx, 0,
                                     VB->Count - VB->Start,
                                     VB->Eye + VB->Start,
                                     VB->Normal + VB->Start,
                                     VB->Fcolor + VB->Start );
            if (ctx->Light.Model.TwoSide) {
               gl_color_shade_vertices( ctx, 1,
                                        VB->Count - VB->Start,
                                        VB->Eye + VB->Start,
                                        VB->Normal + VB->Start,
                                        VB->Bcolor + VB->Start );
            }
         }
      }
   }
   else {
      /* Color index mode */
      if (!VB->MonoMaterial) {
         /* Material may change with each vertex */
         GLuint i;
         /* NOTE the <= here.  This is needed in case glColor/glMaterial
          * is called after the last glVertex inside a glBegin/glEnd pair.
          */
         for (i=VB->Start; i<VB->Count; i++) {
            update_material( ctx, i );
            gl_index_shade_vertices( ctx, 0, 1, &VB->Eye[i],
                                     &VB->Normal[i], &VB->Findex[i] );
            if (ctx->Light.Model.TwoSide) {
               gl_index_shade_vertices( ctx, 1, 1, &VB->Eye[i],
                                        &VB->Normal[i], &VB->Bindex[i] );
            }
         }
         /* Need this in case a glColor/glMaterial is called after the
          * last vertex between glBegin/glEnd.
          */
         update_material( ctx, VB->Count );
      }
      else {
         gl_index_shade_vertices( ctx, 0,
                                  VB->Count - VB->Start,
                                  VB->Eye + VB->Start,
                                  VB->Normal + VB->Start,
                                  VB->Findex + VB->Start );
         if (ctx->Light.Model.TwoSide) {
            gl_index_shade_vertices( ctx, 1,
                                     VB->Count - VB->Start,
                                     VB->Eye + VB->Start,
                                     VB->Normal + VB->Start,
                                     VB->Bindex + VB->Start );
         }
      }
   }
}