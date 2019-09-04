#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * EdgeFlagPtr; scalar_t__ EdgeFlagStrideB; scalar_t__ EdgeFlagStride; } ;
struct TYPE_6__ {TYPE_1__ Array; } ;
typedef  scalar_t__ GLsizei ;
typedef  TYPE_2__ GLcontext ;
typedef  int /*<<< orphan*/  GLboolean ;

/* Variables and functions */
 int /*<<< orphan*/  GL_INVALID_VALUE ; 
 int /*<<< orphan*/  gl_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

void gl_EdgeFlagPointer( GLcontext *ctx,
                         GLsizei stride, const GLboolean *ptr )
{
   if (stride<0) {
      gl_error( ctx, GL_INVALID_VALUE, "glEdgeFlagPointer(stride)" );
      return;
   }
   ctx->Array.EdgeFlagStride = stride;
   ctx->Array.EdgeFlagStrideB = stride ? stride : sizeof(GLboolean);
   ctx->Array.EdgeFlagPtr = (GLboolean *) ptr;
}