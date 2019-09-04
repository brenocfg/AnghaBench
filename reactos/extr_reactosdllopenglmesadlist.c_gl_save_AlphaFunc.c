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
struct TYPE_8__ {int /*<<< orphan*/  (* AlphaFunc ) (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__) ;} ;
struct TYPE_10__ {TYPE_1__ Exec; scalar_t__ ExecuteFlag; } ;
struct TYPE_9__ {scalar_t__ f; int /*<<< orphan*/  e; } ;
typedef  TYPE_2__ Node ;
typedef  scalar_t__ GLfloat ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  TYPE_3__ GLcontext ;
typedef  scalar_t__ GLclampf ;

/* Variables and functions */
 int /*<<< orphan*/  OPCODE_ALPHA_FUNC ; 
 TYPE_2__* alloc_instruction (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__) ; 

void gl_save_AlphaFunc( GLcontext *ctx, GLenum func, GLclampf ref )
{
   Node *n = alloc_instruction( ctx, OPCODE_ALPHA_FUNC, 2 );
   if (n) {
      n[1].e = func;
      n[2].f = (GLfloat) ref;
   }
   if (ctx->ExecuteFlag) {
      (*ctx->Exec.AlphaFunc)( ctx, func, ref );
   }
}