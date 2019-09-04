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
struct vertex_buffer {double** Color; double** Win; double** Clip; double** TexCoord; scalar_t__* Index; } ;
struct TYPE_8__ {scalar_t__ ShadeModel; } ;
struct TYPE_9__ {TYPE_2__ Light; TYPE_1__* Visual; struct vertex_buffer* VB; } ;
struct TYPE_7__ {double InvRedScale; double InvGreenScale; double InvBlueScale; double InvAlphaScale; } ;
typedef  size_t GLuint ;
typedef  scalar_t__ GLint ;
typedef  double GLfloat ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 double DEPTH_SCALE ; 
 int /*<<< orphan*/  FEEDBACK_TOKEN (TYPE_3__*,double) ; 
 scalar_t__ GL_FLAT ; 
 scalar_t__ GL_POLYGON_TOKEN ; 
 scalar_t__ GL_SMOOTH ; 
 int /*<<< orphan*/  gl_feedback_vertex (TYPE_3__*,double,double,double,double,double*,double,double*) ; 

__attribute__((used)) static void feedback_triangle( GLcontext *ctx,
                               GLuint v0, GLuint v1, GLuint v2, GLuint pv )
{
   struct vertex_buffer *VB = ctx->VB;
   GLfloat color[4];
   GLuint i;
   GLfloat invRedScale   = ctx->Visual->InvRedScale;
   GLfloat invGreenScale = ctx->Visual->InvGreenScale;
   GLfloat invBlueScale  = ctx->Visual->InvBlueScale;
   GLfloat invAlphaScale = ctx->Visual->InvAlphaScale;

   FEEDBACK_TOKEN( ctx, (GLfloat) (GLint) GL_POLYGON_TOKEN );
   FEEDBACK_TOKEN( ctx, (GLfloat) 3 );        /* three vertices */

   if (ctx->Light.ShadeModel==GL_FLAT) {
      /* flat shading - same color for each vertex */
      color[0] = (GLfloat) VB->Color[pv][0] * invRedScale;
      color[1] = (GLfloat) VB->Color[pv][1] * invGreenScale;
      color[2] = (GLfloat) VB->Color[pv][2] * invBlueScale;
      color[3] = (GLfloat) VB->Color[pv][3] * invAlphaScale;
   }

   for (i=0;i<3;i++) {
      GLfloat x, y, z, w;
      GLfloat tc[4];
      GLuint v;
      GLfloat invq;

      if (i==0)       v = v0;
      else if (i==1)  v = v1;
      else            v = v2;

      x = VB->Win[v][0];
      y = VB->Win[v][1];
      z = VB->Win[v][2] / DEPTH_SCALE;
      w = VB->Clip[v][3];

      if (ctx->Light.ShadeModel==GL_SMOOTH) {
         /* smooth shading - different color for each vertex */
         color[0] = VB->Color[v][0] * invRedScale;
         color[1] = VB->Color[v][1] * invGreenScale;
         color[2] = VB->Color[v][2] * invBlueScale;
         color[3] = VB->Color[v][3] * invAlphaScale;
      }

      invq = (VB->TexCoord[v][3]==0.0) ? 1.0 : (1.0F / VB->TexCoord[v][3]);
      tc[0] = VB->TexCoord[v][0] * invq;
      tc[1] = VB->TexCoord[v][1] * invq;
      tc[2] = VB->TexCoord[v][2] * invq;
      tc[3] = VB->TexCoord[v][3];

      gl_feedback_vertex( ctx, x, y, z, w, color, (GLfloat) VB->Index[v], tc );
   }
}