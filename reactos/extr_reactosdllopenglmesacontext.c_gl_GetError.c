#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ErrorValue; } ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  TYPE_1__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
 int /*<<< orphan*/  GL_NO_ERROR ; 
 scalar_t__ INSIDE_BEGIN_END (TYPE_1__*) ; 
 int /*<<< orphan*/  gl_error (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 

GLenum gl_GetError( GLcontext *ctx )
{
   GLenum e;

   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glGetError" );
      return GL_INVALID_OPERATION;
   }

   e = ctx->ErrorValue;
   ctx->ErrorValue = GL_NO_ERROR;
   return e;
}