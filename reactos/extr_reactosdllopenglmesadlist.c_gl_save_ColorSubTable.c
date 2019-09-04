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
struct gl_image {int RefCount; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* ColorSubTable ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gl_image*) ;} ;
struct TYPE_10__ {TYPE_1__ Exec; scalar_t__ ExecuteFlag; } ;
struct TYPE_9__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  i; int /*<<< orphan*/  e; } ;
typedef  TYPE_2__ Node ;
typedef  int /*<<< orphan*/  GLvoid ;
typedef  int /*<<< orphan*/  GLsizei ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  OPCODE_COLOR_SUB_TABLE ; 
 TYPE_2__* alloc_instruction (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gl_image*) ; 

void gl_save_ColorSubTable( GLcontext *ctx, GLenum target,
                            GLsizei start, struct gl_image *data )
{
   Node *n = alloc_instruction( ctx, OPCODE_COLOR_SUB_TABLE, 3 );
   if (n) {
      n[1].e = target;
      n[2].i = start;
      n[3].data = (GLvoid *) data;
      if (data) {
         /* must retain this image */
         data->RefCount = 1;
      }
   }
   if (ctx->ExecuteFlag) {
      (*ctx->Exec.ColorSubTable)( ctx, target, start, data );
   }
}