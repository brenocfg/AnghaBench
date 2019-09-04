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
struct TYPE_6__ {scalar_t__ StippleFlag; } ;
struct TYPE_7__ {int* PolygonStipple; int /*<<< orphan*/  NewState; TYPE_1__ Polygon; } ;
typedef  int GLubyte ;
typedef  int GLint ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
 scalar_t__ INSIDE_BEGIN_END (TYPE_2__*) ; 
 int /*<<< orphan*/  NEW_RASTER_OPS ; 
 int /*<<< orphan*/  gl_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

void gl_PolygonStipple( GLcontext *ctx, const GLubyte *mask )
{
   GLint i;

   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glPolygonStipple" );
      return;
   }

   /* TODO:  bit twiddling, unpacking */
   for (i=0;i<32;i++) {
      ctx->PolygonStipple[i] = (mask[i*4+0] << 24)
                             | (mask[i*4+1] << 16)
                             | (mask[i*4+2] << 8)
                             | (mask[i*4+3]);
   }

   if (ctx->Polygon.StippleFlag) {
      ctx->NewState |= NEW_RASTER_OPS;
   }
}