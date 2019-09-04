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
struct TYPE_8__ {int /*<<< orphan*/  (* ClearDepth ) (TYPE_3__*,scalar_t__) ;} ;
struct TYPE_10__ {TYPE_1__ Exec; scalar_t__ ExecuteFlag; } ;
struct TYPE_9__ {scalar_t__ f; } ;
typedef  TYPE_2__ Node ;
typedef  scalar_t__ GLfloat ;
typedef  TYPE_3__ GLcontext ;
typedef  scalar_t__ GLclampd ;

/* Variables and functions */
 int /*<<< orphan*/  OPCODE_CLEAR_DEPTH ; 
 TYPE_2__* alloc_instruction (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,scalar_t__) ; 

void gl_save_ClearDepth( GLcontext *ctx, GLclampd depth )
{
   Node *n = alloc_instruction( ctx, OPCODE_CLEAR_DEPTH, 1 );
   if (n) {
      n[1].f = (GLfloat) depth;
   }
   if (ctx->ExecuteFlag) {
      (*ctx->Exec.ClearDepth)( ctx, depth );
   }
}