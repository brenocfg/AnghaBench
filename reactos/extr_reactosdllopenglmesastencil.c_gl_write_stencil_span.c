#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* Buffer; } ;
struct TYPE_4__ {scalar_t__ Stencil; } ;
typedef  int GLuint ;
typedef  int /*<<< orphan*/  GLubyte ;
typedef  int /*<<< orphan*/  GLstencil ;
typedef  int /*<<< orphan*/  GLint ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  MEMCPY (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * STENCIL_ADDRESS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void gl_write_stencil_span( GLcontext *ctx,
                            GLuint n, GLint x, GLint y,
			    const GLubyte stencil[] )
{
   GLstencil *s;

   if (ctx->Buffer->Stencil) {
      s = STENCIL_ADDRESS( x, y );
      MEMCPY( s, stencil, n * sizeof(GLubyte) );
   }
}