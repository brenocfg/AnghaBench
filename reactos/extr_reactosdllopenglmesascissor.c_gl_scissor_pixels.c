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
struct TYPE_4__ {scalar_t__ Xmin; scalar_t__ Xmax; scalar_t__ Ymin; scalar_t__ Ymax; } ;
typedef  size_t GLuint ;
typedef  int GLubyte ;
typedef  scalar_t__ const GLint ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */

GLuint gl_scissor_pixels( GLcontext *ctx,
                          GLuint n, const GLint x[], const GLint y[],
                          GLubyte mask[] )
{
   GLint xmin = ctx->Buffer->Xmin;
   GLint xmax = ctx->Buffer->Xmax;
   GLint ymin = ctx->Buffer->Ymin;
   GLint ymax = ctx->Buffer->Ymax;
   GLuint i;

   for (i=0;i<n;i++) {
      mask[i] &= (x[i]>=xmin) & (x[i]<=xmax) & (y[i]>=ymin) & (y[i]<=ymax);
   }

   return 1;
}