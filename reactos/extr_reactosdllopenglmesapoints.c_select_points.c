#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vertex_buffer {scalar_t__* ClipMask; int** Win; } ;
struct TYPE_4__ {struct vertex_buffer* VB; } ;
typedef  size_t GLuint ;
typedef  TYPE_1__ GLcontext ;

/* Variables and functions */
 int DEPTH_SCALE ; 
 int /*<<< orphan*/  gl_update_hitflag (TYPE_1__*,int) ; 

__attribute__((used)) static void select_points( GLcontext *ctx, GLuint first, GLuint last )
{
   struct vertex_buffer *VB = ctx->VB;
   GLuint i;

   for (i=first;i<=last;i++) {
      if (VB->ClipMask[i]==0) {
         gl_update_hitflag( ctx, VB->Win[i][2] / DEPTH_SCALE );
      }
   }
}