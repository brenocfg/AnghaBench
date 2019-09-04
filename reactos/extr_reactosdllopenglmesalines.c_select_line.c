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
struct TYPE_6__ {TYPE_1__* VB; } ;
struct TYPE_5__ {int** Win; } ;
typedef  size_t GLuint ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
 int DEPTH_SCALE ; 
 int /*<<< orphan*/  gl_update_hitflag (TYPE_2__*,int) ; 

__attribute__((used)) static void select_line( GLcontext *ctx, GLuint v1, GLuint v2, GLuint pv )
{
   gl_update_hitflag( ctx, ctx->VB->Win[v1][2] / DEPTH_SCALE );
   gl_update_hitflag( ctx, ctx->VB->Win[v2][2] / DEPTH_SCALE );
}