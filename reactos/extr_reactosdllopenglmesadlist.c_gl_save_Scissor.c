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
struct TYPE_8__ {int /*<<< orphan*/  (* Scissor ) (TYPE_3__*,void*,void*,void*,void*) ;} ;
struct TYPE_10__ {TYPE_1__ Exec; scalar_t__ ExecuteFlag; } ;
struct TYPE_9__ {void* i; } ;
typedef  TYPE_2__ Node ;
typedef  void* GLsizei ;
typedef  void* GLint ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  OPCODE_SCISSOR ; 
 TYPE_2__* alloc_instruction (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,void*,void*,void*,void*) ; 

void gl_save_Scissor( GLcontext *ctx,
                      GLint x, GLint y, GLsizei width, GLsizei height )
{
   Node *n = alloc_instruction( ctx, OPCODE_SCISSOR, 4 );
   if (n) {
      n[1].i = x;
      n[2].i = y;
      n[3].i = width;
      n[4].i = height;
   }
   if (ctx->ExecuteFlag) {
      (*ctx->Exec.Scissor)( ctx, x, y, width, height );
   }
}