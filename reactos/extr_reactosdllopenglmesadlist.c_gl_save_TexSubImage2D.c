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
struct TYPE_8__ {int /*<<< orphan*/  (* TexSubImage2D ) (TYPE_3__*,void*,void*,void*,void*,scalar_t__,scalar_t__,void*,void*,struct gl_image*) ;} ;
struct TYPE_10__ {TYPE_1__ Exec; scalar_t__ ExecuteFlag; } ;
struct TYPE_9__ {struct gl_image* data; void* e; void* i; } ;
typedef  TYPE_2__ Node ;
typedef  scalar_t__ GLsizei ;
typedef  void* GLint ;
typedef  void* GLenum ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  OPCODE_TEX_SUB_IMAGE2D ; 
 TYPE_2__* alloc_instruction (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,void*,void*,void*,void*,scalar_t__,scalar_t__,void*,void*,struct gl_image*) ; 

void gl_save_TexSubImage2D( GLcontext *ctx,
                            GLenum target, GLint level,
                            GLint xoffset, GLint yoffset,
                            GLsizei width, GLsizei height,
                            GLenum format, GLenum type,
                            struct gl_image *image )
{
   Node *n = alloc_instruction( ctx, OPCODE_TEX_SUB_IMAGE2D, 9 );
   if (n) {
      n[1].e = target;
      n[2].i = level;
      n[3].i = xoffset;
      n[4].i = yoffset;
      n[5].i = (GLint) width;
      n[6].i = (GLint) height;
      n[7].e = format;
      n[8].e = type;
      n[9].data = image;
      if (image)
         image->RefCount = 1;
   }
   if (ctx->ExecuteFlag) {
      (*ctx->Exec.TexSubImage2D)( ctx, target, level, xoffset, yoffset,
                           width, height, format, type, image );
   }
}