#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int ColorMaterialFace; int ColorMaterialMode; int /*<<< orphan*/  ColorMaterialBitmask; } ;
struct TYPE_7__ {TYPE_1__ Light; } ;
typedef  int GLenum ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
#define  GL_AMBIENT 135 
#define  GL_AMBIENT_AND_DIFFUSE 134 
#define  GL_BACK 133 
#define  GL_DIFFUSE 132 
#define  GL_EMISSION 131 
#define  GL_FRONT 130 
#define  GL_FRONT_AND_BACK 129 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
#define  GL_SPECULAR 128 
 scalar_t__ INSIDE_BEGIN_END (TYPE_2__*) ; 
 int /*<<< orphan*/  gl_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gl_material_bitmask (int,int) ; 

void gl_ColorMaterial( GLcontext *ctx, GLenum face, GLenum mode )
{
   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glColorMaterial" );
      return;
   }
   switch (face) {
      case GL_FRONT:
      case GL_BACK:
      case GL_FRONT_AND_BACK:
         ctx->Light.ColorMaterialFace = face;
         break;
      default:
         gl_error( ctx, GL_INVALID_ENUM, "glColorMaterial(face)" );
         return;
   }
   switch (mode) {
      case GL_EMISSION:
      case GL_AMBIENT:
      case GL_DIFFUSE:
      case GL_SPECULAR:
      case GL_AMBIENT_AND_DIFFUSE:
         ctx->Light.ColorMaterialMode = mode;
         break;
      default:
         gl_error( ctx, GL_INVALID_ENUM, "glColorMaterial(mode)" );
         return;
   }

   ctx->Light.ColorMaterialBitmask = gl_material_bitmask( face, mode );
}