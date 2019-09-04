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
struct TYPE_8__ {int /*<<< orphan*/  (* CallLists ) (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ;} ;
struct TYPE_10__ {TYPE_1__ Exec; scalar_t__ ExecuteFlag; } ;
struct TYPE_9__ {scalar_t__ ui; } ;
typedef  TYPE_2__ Node ;
typedef  int /*<<< orphan*/  GLvoid ;
typedef  scalar_t__ GLuint ;
typedef  scalar_t__ GLsizei ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  OPCODE_CALL_LIST_OFFSET ; 
 TYPE_2__* alloc_instruction (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 scalar_t__ translate_id (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

void gl_save_CallLists( GLcontext *ctx,
                        GLsizei n, GLenum type, const GLvoid *lists )
{
   GLuint i;

   for (i=0;i<n;i++) {
      GLuint list = translate_id( i, type, lists );
      Node *n = alloc_instruction( ctx, OPCODE_CALL_LIST_OFFSET, 1 );
      if (n) {
         n[1].ui = list;
      }
   }
   if (ctx->ExecuteFlag) {
      (*ctx->Exec.CallLists)( ctx, n, type, lists );
   }
}