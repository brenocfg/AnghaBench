#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct gl_image {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* Bitmap ) (TYPE_3__*,scalar_t__,scalar_t__,void*,void*,void*,void*,struct gl_image const*) ;} ;
struct TYPE_10__ {TYPE_1__ Exec; scalar_t__ ExecuteFlag; } ;
struct TYPE_9__ {void* data; void* f; void* i; } ;
typedef  TYPE_2__ Node ;
typedef  scalar_t__ GLsizei ;
typedef  void* GLint ;
typedef  void* GLfloat ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  OPCODE_BITMAP ; 
 TYPE_2__* alloc_instruction (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,scalar_t__,scalar_t__,void*,void*,void*,void*,struct gl_image const*) ; 

void gl_save_Bitmap( GLcontext *ctx,
                     GLsizei width, GLsizei height,
		     GLfloat xorig, GLfloat yorig,
		     GLfloat xmove, GLfloat ymove,
		     const struct gl_image *bitmap )
{
   Node *n = alloc_instruction( ctx, OPCODE_BITMAP, 7 );
   if (n) {
      n[1].i = (GLint) width;
      n[2].i = (GLint) height;
      n[3].f = xorig;
      n[4].f = yorig;
      n[5].f = xmove;
      n[6].f = ymove;
      n[7].data = (void *) bitmap;
   }
   if (ctx->ExecuteFlag) {
      (*ctx->Exec.Bitmap)( ctx, width, height,
                    xorig, yorig, xmove, ymove, bitmap );
   }
}