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
struct TYPE_8__ {int /*<<< orphan*/  (* TexCoord4f ) (TYPE_3__*,void*,void*,void*,void*) ;} ;
struct TYPE_10__ {TYPE_1__ Exec; scalar_t__ ExecuteFlag; } ;
struct TYPE_9__ {void* f; } ;
typedef  TYPE_2__ Node ;
typedef  void* GLfloat ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  OPCODE_TEXCOORD4 ; 
 TYPE_2__* alloc_instruction (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,void*,void*,void*,void*) ; 

void gl_save_TexCoord4f( GLcontext *ctx, GLfloat s, GLfloat t,
                                         GLfloat r, GLfloat q )
{
   Node *n = alloc_instruction( ctx, OPCODE_TEXCOORD4, 4 );
   if (n) {
      n[1].f = s;
      n[2].f = t;
      n[3].f = r;
      n[4].f = q;
   }
   if (ctx->ExecuteFlag) {
      (*ctx->Exec.TexCoord4f)( ctx, s, t, r, q );
   }
}