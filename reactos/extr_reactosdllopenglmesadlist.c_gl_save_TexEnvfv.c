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
struct TYPE_8__ {int /*<<< orphan*/  (* TexEnvfv ) (TYPE_3__*,void*,void*,int /*<<< orphan*/  const*) ;} ;
struct TYPE_10__ {TYPE_1__ Exec; scalar_t__ ExecuteFlag; } ;
struct TYPE_9__ {int /*<<< orphan*/  f; void* e; } ;
typedef  TYPE_2__ Node ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  void* GLenum ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  OPCODE_TEXENV ; 
 TYPE_2__* alloc_instruction (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,void*,void*,int /*<<< orphan*/  const*) ; 

void gl_save_TexEnvfv( GLcontext *ctx,
                       GLenum target, GLenum pname, const GLfloat *params )
{
   Node *n = alloc_instruction( ctx, OPCODE_TEXENV, 6 );
   if (n) {
      n[1].e = target;
      n[2].e = pname;
      n[3].f = params[0];
      n[4].f = params[1];
      n[5].f = params[2];
      n[6].f = params[3];
   }
   if (ctx->ExecuteFlag) {
      (*ctx->Exec.TexEnvfv)( ctx, target, pname, params );
   }
}