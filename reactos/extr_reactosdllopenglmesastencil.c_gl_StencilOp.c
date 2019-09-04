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
struct TYPE_6__ {int FailFunc; int ZFailFunc; int ZPassFunc; } ;
struct TYPE_7__ {TYPE_1__ Stencil; } ;
typedef  int GLenum ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
#define  GL_DECR 133 
#define  GL_INCR 132 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
#define  GL_INVERT 131 
#define  GL_KEEP 130 
#define  GL_REPLACE 129 
#define  GL_ZERO 128 
 scalar_t__ INSIDE_BEGIN_END (TYPE_2__*) ; 
 int /*<<< orphan*/  gl_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

void gl_StencilOp( GLcontext *ctx, GLenum fail, GLenum zfail, GLenum zpass )
{
   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glStencilOp" );
      return;
   }
   switch (fail) {
      case GL_KEEP:
      case GL_ZERO:
      case GL_REPLACE:
      case GL_INCR:
      case GL_DECR:
      case GL_INVERT:
         ctx->Stencil.FailFunc = fail;
         break;
      default:
         gl_error( ctx, GL_INVALID_ENUM, "glStencilOp" );
         return;
   }
   switch (zfail) {
      case GL_KEEP:
      case GL_ZERO:
      case GL_REPLACE:
      case GL_INCR:
      case GL_DECR:
      case GL_INVERT:
         ctx->Stencil.ZFailFunc = zfail;
         break;
      default:
         gl_error( ctx, GL_INVALID_ENUM, "glStencilOp" );
         return;
   }
   switch (zpass) {
      case GL_KEEP:
      case GL_ZERO:
      case GL_REPLACE:
      case GL_INCR:
      case GL_DECR:
      case GL_INVERT:
         ctx->Stencil.ZPassFunc = zpass;
         break;
      default:
         gl_error( ctx, GL_INVALID_ENUM, "glStencilOp" );
         return;
   }
}