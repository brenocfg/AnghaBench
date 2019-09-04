#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void** Normal; } ;
struct TYPE_7__ {TYPE_2__* VB; TYPE_1__ Current; } ;
struct TYPE_6__ {int /*<<< orphan*/  MonoNormal; } ;
typedef  void* GLfloat ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FALSE ; 

void gl_Normal3f( GLcontext *ctx, GLfloat nx, GLfloat ny, GLfloat nz )
{
   ctx->Current.Normal[0] = nx;
   ctx->Current.Normal[1] = ny;
   ctx->Current.Normal[2] = nz;
   ctx->VB->MonoNormal = GL_FALSE;
}