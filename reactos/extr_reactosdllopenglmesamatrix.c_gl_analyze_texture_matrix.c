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
struct TYPE_3__ {float* TextureMatrix; int /*<<< orphan*/  NewTextureMatrix; int /*<<< orphan*/  TextureMatrixType; } ;
typedef  float GLfloat ;
typedef  TYPE_1__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  MATRIX_2D ; 
 int /*<<< orphan*/  MATRIX_3D ; 
 int /*<<< orphan*/  MATRIX_GENERAL ; 
 int /*<<< orphan*/  MATRIX_IDENTITY ; 
 scalar_t__ is_identity (float const*) ; 

void gl_analyze_texture_matrix( GLcontext *ctx )
{
   const GLfloat *m = ctx->TextureMatrix;
   if (is_identity(m)) {
      ctx->TextureMatrixType = MATRIX_IDENTITY;
   }
   else if (                               m[ 8]==0.0F               
            &&                             m[ 9]==0.0F
            && m[2]==0.0F && m[6]==0.0F && m[10]==1.0F && m[14]==0.0F
            && m[3]==0.0F && m[7]==0.0F && m[11]==0.0F && m[15]==1.0F) {
      ctx->TextureMatrixType = MATRIX_2D;
   }
   else if (m[3]==0.0F && m[7]==0.0F && m[11]==0.0F && m[15]==1.0F) {
      ctx->TextureMatrixType = MATRIX_3D;
   }
   else {
      ctx->TextureMatrixType = MATRIX_GENERAL;
   }

   ctx->NewTextureMatrix = GL_FALSE;
}