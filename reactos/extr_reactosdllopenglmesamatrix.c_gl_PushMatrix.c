#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int MatrixMode; } ;
struct TYPE_8__ {size_t ModelViewStackDepth; size_t ProjectionStackDepth; size_t TextureStackDepth; int /*<<< orphan*/  TextureMatrix; int /*<<< orphan*/ * TextureStack; int /*<<< orphan*/ ** NearFarStack; int /*<<< orphan*/  ProjectionMatrix; int /*<<< orphan*/ * ProjectionStack; int /*<<< orphan*/  ModelViewMatrix; int /*<<< orphan*/ * ModelViewStack; TYPE_1__ Transform; } ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
#define  GL_MODELVIEW 130 
#define  GL_PROJECTION 129 
 int /*<<< orphan*/  GL_STACK_OVERFLOW ; 
#define  GL_TEXTURE 128 
 scalar_t__ INSIDE_BEGIN_END (TYPE_2__*) ; 
 int /*<<< orphan*/  MAX_MODELVIEW_STACK_DEPTH ; 
 size_t MAX_PROJECTION_STACK_DEPTH ; 
 size_t MAX_TEXTURE_STACK_DEPTH ; 
 int /*<<< orphan*/  MEMCPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gl_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gl_problem (TYPE_2__*,char*) ; 

void gl_PushMatrix( GLcontext *ctx )
{
   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx,  GL_INVALID_OPERATION, "glPushMatrix" );
      return;
   }
   switch (ctx->Transform.MatrixMode) {
      case GL_MODELVIEW:
         if (ctx->ModelViewStackDepth>=MAX_MODELVIEW_STACK_DEPTH-1) {
            gl_error( ctx,  GL_STACK_OVERFLOW, "glPushMatrix");
            return;
         }
         MEMCPY( ctx->ModelViewStack[ctx->ModelViewStackDepth],
                 ctx->ModelViewMatrix,
                 16*sizeof(GLfloat) );
         ctx->ModelViewStackDepth++;
         break;
      case GL_PROJECTION:
         if (ctx->ProjectionStackDepth>=MAX_PROJECTION_STACK_DEPTH) {
            gl_error( ctx,  GL_STACK_OVERFLOW, "glPushMatrix");
            return;
         }
         MEMCPY( ctx->ProjectionStack[ctx->ProjectionStackDepth],
                 ctx->ProjectionMatrix,
                 16*sizeof(GLfloat) );
         ctx->ProjectionStackDepth++;

         /* Save near and far projection values */
         ctx->NearFarStack[ctx->ProjectionStackDepth][0]
            = ctx->NearFarStack[ctx->ProjectionStackDepth-1][0];
         ctx->NearFarStack[ctx->ProjectionStackDepth][1]
            = ctx->NearFarStack[ctx->ProjectionStackDepth-1][1];
         break;
      case GL_TEXTURE:
         if (ctx->TextureStackDepth>=MAX_TEXTURE_STACK_DEPTH) {
            gl_error( ctx,  GL_STACK_OVERFLOW, "glPushMatrix");
            return;
         }
         MEMCPY( ctx->TextureStack[ctx->TextureStackDepth],
                 ctx->TextureMatrix,
                 16*sizeof(GLfloat) );
         ctx->TextureStackDepth++;
         break;
      default:
         gl_problem(ctx, "Bad matrix mode in gl_PushMatrix");
   }
}