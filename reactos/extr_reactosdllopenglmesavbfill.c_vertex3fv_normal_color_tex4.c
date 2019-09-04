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
struct vertex_buffer {size_t Count; int /*<<< orphan*/ * Edgeflag; int /*<<< orphan*/ * TexCoord; int /*<<< orphan*/ * Normal; int /*<<< orphan*/ * Fcolor; int /*<<< orphan*/ * Obj; } ;
struct TYPE_5__ {int /*<<< orphan*/  EdgeFlag; int /*<<< orphan*/  TexCoord; int /*<<< orphan*/  const* Normal; int /*<<< orphan*/  ByteColor; } ;
struct TYPE_6__ {TYPE_1__ Current; struct vertex_buffer* VB; } ;
typedef  size_t GLuint ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  COPY_3V (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  COPY_4UBV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COPY_4V (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_FALSE ; 
 size_t VB_MAX ; 
 int /*<<< orphan*/  gl_transform_vb_part1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vertex3fv_normal_color_tex4( GLcontext *ctx, const GLfloat v[3] )
{
   struct vertex_buffer *VB = ctx->VB;
   GLuint count = VB->Count;

   COPY_3V( VB->Obj[count], v );
   COPY_4UBV( VB->Fcolor[count], ctx->Current.ByteColor );
   COPY_3V( VB->Normal[count], ctx->Current.Normal );
   COPY_4V( VB->TexCoord[count], ctx->Current.TexCoord );
   VB->Edgeflag[count] = ctx->Current.EdgeFlag;

   count++;
   VB->Count = count;
   if (count==VB_MAX) {
      gl_transform_vb_part1( ctx, GL_FALSE );
   }
}