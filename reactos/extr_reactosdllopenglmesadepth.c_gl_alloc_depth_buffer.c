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
struct TYPE_6__ {int /*<<< orphan*/  Test; } ;
struct TYPE_8__ {TYPE_1__ Depth; TYPE_2__* Buffer; } ;
struct TYPE_7__ {int Width; int Height; int /*<<< orphan*/ * Depth; } ;
typedef  int /*<<< orphan*/  GLdepth ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl_error (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ malloc (int) ; 

void gl_alloc_depth_buffer( GLcontext* ctx )
{
   /* deallocate current depth buffer if present */
   if (ctx->Buffer->Depth) {
      free(ctx->Buffer->Depth);
      ctx->Buffer->Depth = NULL;
   }

   /* allocate new depth buffer, but don't initialize it */
   ctx->Buffer->Depth = (GLdepth *) malloc( ctx->Buffer->Width
                                            * ctx->Buffer->Height
                                            * sizeof(GLdepth) );
   if (!ctx->Buffer->Depth) {
      /* out of memory */
      ctx->Depth.Test = GL_FALSE;
      gl_error( ctx, GL_OUT_OF_MEMORY, "Couldn't allocate depth buffer" );
   }
}