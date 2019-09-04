#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  Enabled; } ;
struct TYPE_8__ {TYPE_1__ Stencil; TYPE_2__* Buffer; } ;
struct TYPE_7__ {int Width; int Height; int /*<<< orphan*/ * Stencil; } ;
typedef  int GLuint ;
typedef  int /*<<< orphan*/  GLstencil ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl_error (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ malloc (int) ; 

void gl_alloc_stencil_buffer( GLcontext *ctx )
{
   GLuint buffersize = ctx->Buffer->Width * ctx->Buffer->Height;

   /* deallocate current stencil buffer if present */
   if (ctx->Buffer->Stencil) {
      free(ctx->Buffer->Stencil);
      ctx->Buffer->Stencil = NULL;
   }

   /* allocate new stencil buffer */
   ctx->Buffer->Stencil = (GLstencil *) malloc(buffersize * sizeof(GLstencil));
   if (!ctx->Buffer->Stencil) {
      /* out of memory */
      ctx->Stencil.Enabled = GL_FALSE;
      gl_error( ctx, GL_OUT_OF_MEMORY, "gl_alloc_stencil_buffer" );
   }
}