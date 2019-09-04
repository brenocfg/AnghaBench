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
struct TYPE_8__ {int /*<<< orphan*/  (* Rectf ) (TYPE_3__*,void*,void*,void*,void*) ;} ;
struct TYPE_10__ {TYPE_1__ Exec; scalar_t__ ExecuteFlag; } ;
struct TYPE_9__ {void* f; } ;
typedef  TYPE_2__ Node ;
typedef  void* GLfloat ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  OPCODE_RECTF ; 
 TYPE_2__* alloc_instruction (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,void*,void*,void*,void*) ; 

void gl_save_Rectf( GLcontext *ctx,
                    GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2 )
{
   Node *n = alloc_instruction( ctx, OPCODE_RECTF, 4 );
   if (n) {
      n[1].f = x1;
      n[2].f = y1;
      n[3].f = x2;
      n[4].f = y2;
   }
   if (ctx->ExecuteFlag) {
      (*ctx->Exec.Rectf)( ctx, x1, y1, x2, y2 );
   }
}