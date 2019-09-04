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
struct TYPE_3__ {int ModelViewMatrixType; int* ModelViewMatrix; } ;
typedef  size_t GLuint ;
typedef  int GLfloat ;
typedef  TYPE_1__ GLcontext ;

/* Variables and functions */
#define  MATRIX_2D 132 
#define  MATRIX_2D_NO_ROT 131 
#define  MATRIX_3D 130 
#define  MATRIX_GENERAL 129 
#define  MATRIX_IDENTITY 128 
 int /*<<< orphan*/  gl_problem (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void transform_points4( GLcontext *ctx, GLuint n,
                               /*const*/ GLfloat vObj[][4], GLfloat vEye[][4] )
{
#ifndef USE_ASM
   switch (ctx->ModelViewMatrixType) {
      case MATRIX_GENERAL:
         {
            const GLfloat *m = ctx->ModelViewMatrix;
            GLfloat m0 = m[0],  m4 = m[4],  m8 = m[8],  m12 = m[12];
            GLfloat m1 = m[1],  m5 = m[5],  m9 = m[9],  m13 = m[13];
            GLfloat m2 = m[2],  m6 = m[6],  m10 = m[10],  m14 = m[14];
            GLfloat m3 = m[3],  m7 = m[7],  m11 = m[11],  m15 = m[15];
            GLuint i;
            for (i=0;i<n;i++) {
               GLfloat ox = vObj[i][0], oy = vObj[i][1];
               GLfloat oz = vObj[i][2], ow = vObj[i][3];
               vEye[i][0] = m0 * ox + m4 * oy + m8  * oz + m12 * ow;
               vEye[i][1] = m1 * ox + m5 * oy + m9  * oz + m13 * ow;
               vEye[i][2] = m2 * ox + m6 * oy + m10 * oz + m14 * ow;
               vEye[i][3] = m3 * ox + m7 * oy + m11 * oz + m15 * ow;
            }
         }
         break;
      case MATRIX_IDENTITY:
         {
            GLuint i;
            for (i=0;i<n;i++) {
               vEye[i][0] = vObj[i][0];
               vEye[i][1] = vObj[i][1];
               vEye[i][2] = vObj[i][2];
               vEye[i][3] = vObj[i][3];
            }
         }
         break;
      case MATRIX_2D:
         {
            const GLfloat *m = ctx->ModelViewMatrix;
            GLfloat m0 = m[0], m1 = m[1], m4 = m[4], m5 = m[5];
            GLfloat m12 = m[12], m13 = m[13];
            GLuint i;
            for (i=0;i<n;i++) {
               GLfloat ox = vObj[i][0], oy = vObj[i][1];
               GLfloat oz = vObj[i][2], ow = vObj[i][3];
               vEye[i][0] = m0 * ox + m4 * oy            + m12 * ow;
               vEye[i][1] = m1 * ox + m5 * oy            + m13 * ow;
               vEye[i][2] =                   +       oz           ;
               vEye[i][3] =                                      ow;
            }
         }
         break;
      case MATRIX_2D_NO_ROT:
         {
            const GLfloat *m = ctx->ModelViewMatrix;
            GLfloat m0 = m[0], m5 = m[5], m12 = m[12], m13 = m[13];
            GLuint i;
            for (i=0;i<n;i++) {
               GLfloat ox = vObj[i][0], oy = vObj[i][1];
               GLfloat oz = vObj[i][2], ow = vObj[i][3];
               vEye[i][0] = m0 * ox                      + m12 * ow;
               vEye[i][1] =           m5 * oy            + m13 * ow;
               vEye[i][2] =                   +       oz           ;
               vEye[i][3] =                                      ow;
            }
         }
         break;
      case MATRIX_3D:
         {
            const GLfloat *m = ctx->ModelViewMatrix;
            GLfloat m0 = m[0], m1 = m[1], m2 = m[2], m4 = m[4], m5 = m[5];
            GLfloat m6 = m[6], m8 = m[8], m9 = m[9], m10 = m[10];
            GLfloat m12 = m[12], m13 = m[13], m14 = m[14];
            GLuint i;
            for (i=0;i<n;i++) {
               GLfloat ox = vObj[i][0], oy = vObj[i][1];
               GLfloat oz = vObj[i][2], ow = vObj[i][3];
               vEye[i][0] = m0 * ox + m4 * oy +  m8 * oz + m12 * ow;
               vEye[i][1] = m1 * ox + m5 * oy +  m9 * oz + m13 * ow;
               vEye[i][2] = m2 * ox + m6 * oy + m10 * oz + m14 * ow;
               vEye[i][3] =                                      ow;
            }
         }
         break;
      default:
         /* should never get here */
         gl_problem( NULL, "invalid matrix type in transform_points4()" );
   }
#else
   switch (ctx->ModelViewMatrixType) {
      case MATRIX_GENERAL:
         asm_transform_points4_general( n, vEye, ctx->ModelViewMatrix, vObj );
         break;
      case MATRIX_IDENTITY:
         asm_transform_points4_identity( n, vEye, vObj );
         break;
      case MATRIX_2D:
         asm_transform_points4_2d( n, vEye, ctx->ModelViewMatrix, vObj );
         break;
      case MATRIX_2D_NO_ROT:
         asm_transform_points4_2d_no_rot( n, vEye, ctx->ModelViewMatrix,
                                          vObj );
         break;
      case MATRIX_3D:
         asm_transform_points4_3d( n, vEye, ctx->ModelViewMatrix, vObj );
         break;
      default:
         /* should never get here */
         gl_problem( NULL, "invalid matrix type in transform_points4()" );
         return;
   }
#endif
}