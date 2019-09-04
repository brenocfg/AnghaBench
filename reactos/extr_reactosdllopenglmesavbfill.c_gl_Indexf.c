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
struct TYPE_5__ {scalar_t__ Index; } ;
struct TYPE_7__ {TYPE_2__* VB; TYPE_1__ Current; } ;
struct TYPE_6__ {int /*<<< orphan*/  MonoColor; } ;
typedef  scalar_t__ GLuint ;
typedef  scalar_t__ GLint ;
typedef  scalar_t__ GLfloat ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FALSE ; 

void gl_Indexf( GLcontext *ctx, GLfloat c )
{
   ctx->Current.Index = (GLuint) (GLint) c;
   ctx->VB->MonoColor = GL_FALSE;
}