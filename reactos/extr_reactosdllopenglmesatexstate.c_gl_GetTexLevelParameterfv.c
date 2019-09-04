#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ GLint ;
typedef  scalar_t__ GLfloat ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  int /*<<< orphan*/  GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  gl_GetTexLevelParameteriv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 

void gl_GetTexLevelParameterfv( GLcontext *ctx, GLenum target, GLint level,
                                GLenum pname, GLfloat *params )
{
   GLint iparam;

   gl_GetTexLevelParameteriv( ctx, target, level, pname, &iparam );
   *params = (GLfloat) iparam;
}