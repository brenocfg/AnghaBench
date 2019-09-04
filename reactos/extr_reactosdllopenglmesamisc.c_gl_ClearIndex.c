#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ ClearIndex; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* ClearIndex ) (TYPE_4__*,scalar_t__) ;} ;
struct TYPE_12__ {TYPE_3__ Color; TYPE_2__ Driver; TYPE_1__* Visual; } ;
struct TYPE_9__ {int /*<<< orphan*/  RGBAflag; } ;
typedef  scalar_t__ GLuint ;
typedef  scalar_t__ GLfloat ;
typedef  TYPE_4__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
 scalar_t__ INSIDE_BEGIN_END (TYPE_4__*) ; 
 int /*<<< orphan*/  gl_error (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,scalar_t__) ; 

void gl_ClearIndex( GLcontext *ctx, GLfloat c )
{
   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glClearIndex" );
      return;
   }
   ctx->Color.ClearIndex = (GLuint) c;
   if (!ctx->Visual->RGBAflag) {
      /* it's OK to call glClearIndex in RGBA mode but it should be a NOP */
      (*ctx->Driver.ClearIndex)( ctx, ctx->Color.ClearIndex );
   }
}