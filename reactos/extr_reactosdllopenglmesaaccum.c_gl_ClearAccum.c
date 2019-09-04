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
struct TYPE_6__ {void** ClearColor; } ;
struct TYPE_7__ {TYPE_1__ Accum; } ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
 void* CLAMP (int /*<<< orphan*/ ,double,double) ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
 scalar_t__ INSIDE_BEGIN_END (TYPE_2__*) ; 
 int /*<<< orphan*/  gl_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

void gl_ClearAccum( GLcontext *ctx,
                    GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha )
{
   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glAccum" );
      return;
   }
   ctx->Accum.ClearColor[0] = CLAMP( red, -1.0, 1.0 );
   ctx->Accum.ClearColor[1] = CLAMP( green, -1.0, 1.0 );
   ctx->Accum.ClearColor[2] = CLAMP( blue, -1.0, 1.0 );
   ctx->Accum.ClearColor[3] = CLAMP( alpha, -1.0, 1.0 );
}