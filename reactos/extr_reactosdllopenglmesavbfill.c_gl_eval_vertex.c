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
struct vertex_buffer {size_t Count; size_t* Findex; int /*<<< orphan*/ * Edgeflag; int /*<<< orphan*/ * TexCoord; int /*<<< orphan*/ * Fcolor; int /*<<< orphan*/ * Normal; int /*<<< orphan*/ * Obj; int /*<<< orphan*/  MonoNormal; int /*<<< orphan*/  VertexSizeMask; } ;
struct TYPE_5__ {int /*<<< orphan*/  EdgeFlag; } ;
struct TYPE_6__ {TYPE_1__ Current; struct vertex_buffer* VB; } ;
typedef  size_t GLuint ;
typedef  int /*<<< orphan*/  GLubyte ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  COPY_3V (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  COPY_4UBV (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  COPY_4V (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  GL_FALSE ; 
 size_t VB_MAX ; 
 int /*<<< orphan*/  VERTEX4_BIT ; 
 int /*<<< orphan*/  gl_transform_vb_part1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

void gl_eval_vertex( GLcontext *ctx,
                     const GLfloat vertex[4], const GLfloat normal[3],
		     const GLubyte color[4],
                     GLuint index,
                     const GLfloat texcoord[4] )
{
   struct vertex_buffer *VB = ctx->VB;
   GLuint count = VB->Count;  /* copy to local var to encourage optimization */

   VB->VertexSizeMask = VERTEX4_BIT;
   VB->MonoNormal = GL_FALSE;
   COPY_4V( VB->Obj[count], vertex );
   COPY_3V( VB->Normal[count], normal );
   COPY_4UBV( VB->Fcolor[count], color );
   
#ifdef GL_VERSION_1_1
   if (ctx->Light.ColorMaterialEnabled
       && (ctx->Eval.Map1Color4 || ctx->Eval.Map2Color4)) {
      GLfloat fcolor[4];
      fcolor[0] = color[0] * ctx->Visual->InvRedScale;
      fcolor[1] = color[1] * ctx->Visual->InvGreenScale;
      fcolor[2] = color[2] * ctx->Visual->InvBlueScale;
      fcolor[3] = color[3] * ctx->Visual->InvAlphaScale;
      gl_set_material( ctx, ctx->Light.ColorMaterialBitmask, fcolor );
   }
#endif
   VB->Findex[count] = index;
   COPY_4V( VB->TexCoord[count], texcoord );
   VB->Edgeflag[count] = ctx->Current.EdgeFlag;

   count++;
   VB->Count = count;
   if (count==VB_MAX) {
      gl_transform_vb_part1( ctx, GL_FALSE );
   }
}