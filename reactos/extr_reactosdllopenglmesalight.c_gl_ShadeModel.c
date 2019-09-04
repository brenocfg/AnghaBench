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
struct TYPE_6__ {int ShadeModel; } ;
struct TYPE_7__ {int /*<<< orphan*/  NewState; TYPE_1__ Light; } ;
typedef  int GLenum ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
#define  GL_FLAT 129 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
#define  GL_SMOOTH 128 
 scalar_t__ INSIDE_BEGIN_END (TYPE_2__*) ; 
 int /*<<< orphan*/  NEW_RASTER_OPS ; 
 int /*<<< orphan*/  gl_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

void gl_ShadeModel( GLcontext *ctx, GLenum mode )
{
   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glShadeModel" );
      return;
   }

   switch (mode) {
      case GL_FLAT:
      case GL_SMOOTH:
         if (ctx->Light.ShadeModel!=mode) {
            ctx->Light.ShadeModel = mode;
            ctx->NewState |= NEW_RASTER_OPS;
         }
         break;
      default:
         gl_error( ctx, GL_INVALID_ENUM, "glShadeModel" );
   }
}