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
struct TYPE_6__ {scalar_t__ FrontMode; scalar_t__ BackMode; int /*<<< orphan*/  Unfilled; } ;
struct TYPE_7__ {int /*<<< orphan*/  NewState; TYPE_1__ Polygon; } ;
typedef  scalar_t__ GLenum ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
 scalar_t__ GL_BACK ; 
 int /*<<< orphan*/  GL_FALSE ; 
 scalar_t__ GL_FILL ; 
 scalar_t__ GL_FRONT ; 
 scalar_t__ GL_FRONT_AND_BACK ; 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
 scalar_t__ GL_LINE ; 
 scalar_t__ GL_POINT ; 
 int /*<<< orphan*/  GL_TRUE ; 
 scalar_t__ INSIDE_BEGIN_END (TYPE_2__*) ; 
 int /*<<< orphan*/  NEW_POLYGON ; 
 int /*<<< orphan*/  gl_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

void gl_PolygonMode( GLcontext *ctx, GLenum face, GLenum mode )
{
   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glPolygonMode" );
      return;
   }
   if (face!=GL_FRONT && face!=GL_BACK && face!=GL_FRONT_AND_BACK) {
      gl_error( ctx, GL_INVALID_ENUM, "glPolygonMode(face)" );
      return;
   }
   else if (mode!=GL_POINT && mode!=GL_LINE && mode!=GL_FILL) {
      gl_error( ctx, GL_INVALID_ENUM, "glPolygonMode(mode)" );
      return;
   }

   if (face==GL_FRONT || face==GL_FRONT_AND_BACK) {
      ctx->Polygon.FrontMode = mode;
   }
   if (face==GL_BACK || face==GL_FRONT_AND_BACK) {
      ctx->Polygon.BackMode = mode;
   }

   /* Compute a handy "shortcut" value: */
   if (ctx->Polygon.FrontMode!=GL_FILL || ctx->Polygon.BackMode!=GL_FILL) {
      ctx->Polygon.Unfilled = GL_TRUE;
   }
   else {
      ctx->Polygon.Unfilled = GL_FALSE;
   }

   ctx->NewState |= NEW_POLYGON;
}