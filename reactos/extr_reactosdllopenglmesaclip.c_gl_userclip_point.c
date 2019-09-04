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
struct TYPE_4__ {float const** ClipEquation; scalar_t__* ClipEnabled; } ;
struct TYPE_5__ {TYPE_1__ Transform; } ;
typedef  size_t GLuint ;
typedef  float GLfloat ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
 size_t MAX_CLIP_PLANES ; 

GLuint gl_userclip_point( GLcontext* ctx, const GLfloat v[] )
{
   GLuint p;

   for (p=0;p<MAX_CLIP_PLANES;p++) {
      if (ctx->Transform.ClipEnabled[p]) {
	 GLfloat dot = v[0] * ctx->Transform.ClipEquation[p][0]
		     + v[1] * ctx->Transform.ClipEquation[p][1]
		     + v[2] * ctx->Transform.ClipEquation[p][2]
		     + v[3] * ctx->Transform.ClipEquation[p][3];
         if (dot < 0.0F) {
            return 0;
         }
      }
   }

   return 1;
}