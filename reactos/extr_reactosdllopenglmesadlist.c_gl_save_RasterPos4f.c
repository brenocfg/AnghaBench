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
struct TYPE_8__ {int /*<<< orphan*/  (* RasterPos4f ) (TYPE_3__*,void*,void*,void*,void*) ;} ;
struct TYPE_10__ {TYPE_1__ Exec; scalar_t__ ExecuteFlag; } ;
struct TYPE_9__ {void* f; } ;
typedef  TYPE_2__ Node ;
typedef  void* GLfloat ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  OPCODE_RASTER_POS ; 
 TYPE_2__* alloc_instruction (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,void*,void*,void*,void*) ; 

void gl_save_RasterPos4f( GLcontext *ctx,
                          GLfloat x, GLfloat y, GLfloat z, GLfloat w )
{
   Node *n = alloc_instruction( ctx, OPCODE_RASTER_POS, 4 );
   if (n) {
      n[1].f = x;
      n[2].f = y;
      n[3].f = z;
      n[4].f = w;
   }
   if (ctx->ExecuteFlag) {
      (*ctx->Exec.RasterPos4f)( ctx, x, y, z, w );
   }
}