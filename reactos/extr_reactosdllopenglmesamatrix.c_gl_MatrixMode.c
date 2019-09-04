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
struct TYPE_6__ {int MatrixMode; } ;
struct TYPE_7__ {TYPE_1__ Transform; } ;
typedef  int GLenum ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
#define  GL_MODELVIEW 130 
#define  GL_PROJECTION 129 
#define  GL_TEXTURE 128 
 scalar_t__ INSIDE_BEGIN_END (TYPE_2__*) ; 
 int /*<<< orphan*/  gl_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

void gl_MatrixMode( GLcontext *ctx, GLenum mode )
{
   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx,  GL_INVALID_OPERATION, "glMatrixMode" );
      return;
   }
   switch (mode) {
      case GL_MODELVIEW:
      case GL_PROJECTION:
      case GL_TEXTURE:
         ctx->Transform.MatrixMode = mode;
         break;
      default:
         gl_error( ctx,  GL_INVALID_ENUM, "glMatrixMode" );
   }
}