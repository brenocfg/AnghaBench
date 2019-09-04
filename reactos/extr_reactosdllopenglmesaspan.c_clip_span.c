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
struct TYPE_4__ {scalar_t__ Height; scalar_t__ Width; } ;
typedef  int GLuint ;
typedef  scalar_t__ GLubyte ;
typedef  scalar_t__ GLint ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */

__attribute__((used)) static GLuint clip_span( GLcontext *ctx,
                         GLint n, GLint x, GLint y, GLubyte mask[] )
{
   GLint i;

   /* Clip to top and bottom */
   if (y<0 || y>=ctx->Buffer->Height) {
      return 0;
   }

   /* Clip to left and right */
   if (x>=0 && x+n<=ctx->Buffer->Width) {
      /* no clipping needed */
      return 1;
   }
   else if (x+n<=0) {
      /* completely off left side */
      return 0;
   }
   else if (x>=ctx->Buffer->Width) {
      /* completely off right side */
      return 0;
   }
   else {
      /* clip-test each pixel, this could be done better */
      for (i=0;i<n;i++) {
         if (x+i<0 || x+i>=ctx->Buffer->Width) {
            mask[i] = 0;
         }
      }
      return 1;
   }
}