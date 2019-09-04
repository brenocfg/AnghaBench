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
struct vertex_buffer {scalar_t__* ClipMask; float** Win; float** Clip; float** Color; float** TexCoord; scalar_t__* Index; } ;
struct TYPE_8__ {scalar_t__ ShadeModel; } ;
struct TYPE_9__ {TYPE_2__ Light; TYPE_1__* Visual; struct vertex_buffer* VB; } ;
struct TYPE_7__ {float InvRedScale; float InvGreenScale; float InvBlueScale; float InvAlphaScale; } ;
typedef  size_t GLuint ;
typedef  scalar_t__ GLint ;
typedef  float GLfloat ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 float DEPTH_SCALE ; 
 int /*<<< orphan*/  FEEDBACK_TOKEN (TYPE_3__*,float) ; 
 float FixedToFloat (float) ; 
 scalar_t__ GL_POINT_TOKEN ; 
 scalar_t__ GL_SMOOTH ; 
 int /*<<< orphan*/  gl_feedback_vertex (TYPE_3__*,float,float,float,float,float*,float,float*) ; 

__attribute__((used)) static void feedback_points( GLcontext *ctx, GLuint first, GLuint last )
{
   struct vertex_buffer *VB = ctx->VB;
   GLuint i;
   GLfloat invRedScale   = ctx->Visual->InvRedScale;
   GLfloat invGreenScale = ctx->Visual->InvGreenScale;
   GLfloat invBlueScale  = ctx->Visual->InvBlueScale;
   GLfloat invAlphaScale = ctx->Visual->InvAlphaScale;

   for (i=first;i<=last;i++) {
      if (VB->ClipMask[i]==0) {
         GLfloat x, y, z, w, invq;
         GLfloat color[4], texcoord[4];

         x = VB->Win[i][0];
         y = VB->Win[i][1];
         z = VB->Win[i][2] / DEPTH_SCALE;
         w = VB->Clip[i][3];

         /* convert color from integer back to a float in [0,1] */
         if (ctx->Light.ShadeModel==GL_SMOOTH) {
            /* smooth shading - colors are in fixed point */
            color[0] = FixedToFloat(VB->Color[i][0]) * invRedScale;
            color[1] = FixedToFloat(VB->Color[i][1]) * invGreenScale;
            color[2] = FixedToFloat(VB->Color[i][2]) * invBlueScale;
            color[3] = FixedToFloat(VB->Color[i][3]) * invAlphaScale;
         }
         else {
            /* flat shading - colors are integers */
            color[0] = VB->Color[i][0] * invRedScale;
            color[1] = VB->Color[i][1] * invGreenScale;
            color[2] = VB->Color[i][2] * invBlueScale;
            color[3] = VB->Color[i][3] * invAlphaScale;
         }
         invq = 1.0F / VB->TexCoord[i][3];
         texcoord[0] = VB->TexCoord[i][0] * invq;
         texcoord[1] = VB->TexCoord[i][1] * invq;
         texcoord[2] = VB->TexCoord[i][2] * invq;
         texcoord[3] = VB->TexCoord[i][3];

         FEEDBACK_TOKEN( ctx, (GLfloat) (GLint) GL_POINT_TOKEN );
         gl_feedback_vertex( ctx, x, y, z, w, color,
                             (GLfloat) VB->Index[i], texcoord );
      }
   }
}