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
struct TYPE_5__ {int Mode; double Density; double Start; double End; double Index; double* Color; } ;
struct TYPE_6__ {TYPE_1__ Fog; } ;
typedef  int /*<<< orphan*/  GLint ;
typedef  double GLfloat ;
typedef  int GLenum ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
 int GL_EXP ; 
 int GL_EXP2 ; 
#define  GL_FOG_COLOR 133 
#define  GL_FOG_DENSITY 132 
#define  GL_FOG_END 131 
#define  GL_FOG_INDEX 130 
#define  GL_FOG_MODE 129 
#define  GL_FOG_START 128 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_VALUE ; 
 int GL_LINEAR ; 
 int /*<<< orphan*/  gl_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

void gl_Fogfv( GLcontext *ctx, GLenum pname, const GLfloat *params )
{
   GLenum m;

   switch (pname) {
      case GL_FOG_MODE:
         m = (GLenum) (GLint) *params;
	 if (m==GL_LINEAR || m==GL_EXP || m==GL_EXP2) {
	    ctx->Fog.Mode = m;
	 }
	 else {
	    gl_error( ctx, GL_INVALID_ENUM, "glFog" );
	 }
	 break;
      case GL_FOG_DENSITY:
	 if (*params<0.0) {
	    gl_error( ctx, GL_INVALID_VALUE, "glFog" );
	 }
	 else {
	    ctx->Fog.Density = *params;
	 }
	 break;
      case GL_FOG_START:
#ifndef GL_VERSION_1_1
         if (*params<0.0F) {
            gl_error( ctx, GL_INVALID_VALUE, "glFog(GL_FOG_START)" );
            return;
         }
#endif
	 ctx->Fog.Start = *params;
	 break;
      case GL_FOG_END:
#ifndef GL_VERSION_1_1
         if (*params<0.0F) {
            gl_error( ctx, GL_INVALID_VALUE, "glFog(GL_FOG_END)" );
            return;
         }
#endif
	 ctx->Fog.End = *params;
	 break;
      case GL_FOG_INDEX:
	 ctx->Fog.Index = *params;
	 break;
      case GL_FOG_COLOR:
	 ctx->Fog.Color[0] = params[0];
	 ctx->Fog.Color[1] = params[1];
	 ctx->Fog.Color[2] = params[2];
	 ctx->Fog.Color[3] = params[3];
         break;
      default:
         gl_error( ctx, GL_INVALID_ENUM, "glFog" );
   }
}