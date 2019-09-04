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
struct TYPE_8__ {TYPE_1__* Material; } ;
struct TYPE_9__ {TYPE_2__ Light; } ;
struct TYPE_7__ {int /*<<< orphan*/  SpecularIndex; int /*<<< orphan*/  DiffuseIndex; int /*<<< orphan*/  AmbientIndex; int /*<<< orphan*/  Shininess; int /*<<< orphan*/ * Emission; int /*<<< orphan*/ * Specular; int /*<<< orphan*/ * Diffuse; int /*<<< orphan*/ * Ambient; } ;
typedef  size_t GLuint ;
typedef  int /*<<< orphan*/  GLint ;
typedef  scalar_t__ GLenum ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  FLOAT_TO_INT (int /*<<< orphan*/ ) ; 
#define  GL_AMBIENT 133 
 scalar_t__ GL_BACK ; 
#define  GL_COLOR_INDEXES 132 
#define  GL_DIFFUSE 131 
#define  GL_EMISSION 130 
 scalar_t__ GL_FRONT ; 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
#define  GL_SHININESS 129 
#define  GL_SPECULAR 128 
 scalar_t__ INSIDE_BEGIN_END (TYPE_3__*) ; 
 int /*<<< orphan*/  ROUNDF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_error (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 

void gl_GetMaterialiv( GLcontext *ctx,
                       GLenum face, GLenum pname, GLint *params )
{
   GLuint f;

   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glGetMaterialiv" );
      return;
   }
   if (face==GL_FRONT) {
      f = 0;
   }
   else if (face==GL_BACK) {
      f = 1;
   }
   else {
      gl_error( ctx, GL_INVALID_ENUM, "glGetMaterialiv(face)" );
      return;
   }
   switch (pname) {
      case GL_AMBIENT:
         params[0] = FLOAT_TO_INT( ctx->Light.Material[f].Ambient[0] );
         params[1] = FLOAT_TO_INT( ctx->Light.Material[f].Ambient[1] );
         params[2] = FLOAT_TO_INT( ctx->Light.Material[f].Ambient[2] );
         params[3] = FLOAT_TO_INT( ctx->Light.Material[f].Ambient[3] );
         break;
      case GL_DIFFUSE:
         params[0] = FLOAT_TO_INT( ctx->Light.Material[f].Diffuse[0] );
         params[1] = FLOAT_TO_INT( ctx->Light.Material[f].Diffuse[1] );
         params[2] = FLOAT_TO_INT( ctx->Light.Material[f].Diffuse[2] );
         params[3] = FLOAT_TO_INT( ctx->Light.Material[f].Diffuse[3] );
	 break;
      case GL_SPECULAR:
         params[0] = FLOAT_TO_INT( ctx->Light.Material[f].Specular[0] );
         params[1] = FLOAT_TO_INT( ctx->Light.Material[f].Specular[1] );
         params[2] = FLOAT_TO_INT( ctx->Light.Material[f].Specular[2] );
         params[3] = FLOAT_TO_INT( ctx->Light.Material[f].Specular[3] );
	 break;
      case GL_EMISSION:
         params[0] = FLOAT_TO_INT( ctx->Light.Material[f].Emission[0] );
         params[1] = FLOAT_TO_INT( ctx->Light.Material[f].Emission[1] );
         params[2] = FLOAT_TO_INT( ctx->Light.Material[f].Emission[2] );
         params[3] = FLOAT_TO_INT( ctx->Light.Material[f].Emission[3] );
	 break;
      case GL_SHININESS:
         *params = ROUNDF( ctx->Light.Material[f].Shininess );
	 break;
      case GL_COLOR_INDEXES:
	 params[0] = ROUNDF( ctx->Light.Material[f].AmbientIndex );
	 params[1] = ROUNDF( ctx->Light.Material[f].DiffuseIndex );
	 params[2] = ROUNDF( ctx->Light.Material[f].SpecularIndex );
	 break;
      default:
         gl_error( ctx, GL_INVALID_ENUM, "glGetMaterialfv(pname)" );
   }
}