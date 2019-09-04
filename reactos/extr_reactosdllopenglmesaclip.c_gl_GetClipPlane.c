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
struct TYPE_6__ {scalar_t__** ClipEquation; } ;
struct TYPE_7__ {TYPE_1__ Transform; } ;
typedef  size_t GLint ;
typedef  scalar_t__ GLenum ;
typedef  scalar_t__ GLdouble ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
 scalar_t__ GL_CLIP_PLANE0 ; 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
 scalar_t__ INSIDE_BEGIN_END (TYPE_2__*) ; 
 size_t MAX_CLIP_PLANES ; 
 int /*<<< orphan*/  gl_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

void gl_GetClipPlane( GLcontext* ctx, GLenum plane, GLdouble *equation )
{
   GLint p;

   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glGetClipPlane" );
      return;
   }

   p = (GLint) (plane - GL_CLIP_PLANE0);
   if (p<0 || p>=MAX_CLIP_PLANES) {
      gl_error( ctx, GL_INVALID_ENUM, "glGetClipPlane" );
      return;
   }

   equation[0] = (GLdouble) ctx->Transform.ClipEquation[p][0];
   equation[1] = (GLdouble) ctx->Transform.ClipEquation[p][1];
   equation[2] = (GLdouble) ctx->Transform.ClipEquation[p][2];
   equation[3] = (GLdouble) ctx->Transform.ClipEquation[p][3];
}