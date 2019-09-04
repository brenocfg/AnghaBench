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
struct vertex_buffer {double** Eye; size_t Free; } ;
struct TYPE_5__ {double** ClipEquation; scalar_t__* ClipEnabled; } ;
struct TYPE_6__ {scalar_t__ ClipMask; TYPE_1__ Transform; struct vertex_buffer* VB; } ;
typedef  size_t GLuint ;
typedef  double GLfloat ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  EYE_SPACE ; 
 size_t MAX_CLIP_PLANES ; 
 scalar_t__ OUTSIDE (size_t,double,double,double,double) ; 
 size_t VB_SIZE ; 
 int /*<<< orphan*/  interpolate_aux (TYPE_2__*,int /*<<< orphan*/ ,size_t,double,size_t,size_t) ; 

GLuint gl_userclip_line( GLcontext* ctx, GLuint *i, GLuint *j )
{
   struct vertex_buffer* VB = ctx->VB;

   GLuint p, ii, jj;

   ii = *i;
   jj = *j;

   for (p=0;p<MAX_CLIP_PLANES;p++) {
      if (ctx->Transform.ClipEnabled[p]) {
	 register GLfloat a, b, c, d;
	 a = ctx->Transform.ClipEquation[p][0];
	 b = ctx->Transform.ClipEquation[p][1];
	 c = ctx->Transform.ClipEquation[p][2];
	 d = ctx->Transform.ClipEquation[p][3];

         if (OUTSIDE( ii, a,b,c,d  )) {
            if (OUTSIDE( jj, a,b,c,d )) {
               /* ii and jj outside ==> quit */
               return 0;
            }
            else {
               /* ii is outside, jj is inside ==> clip */
               GLfloat dx, dy, dz, dw, t, denom;
               dx = VB->Eye[ii][0] - VB->Eye[jj][0];
               dy = VB->Eye[ii][1] - VB->Eye[jj][1];
               dz = VB->Eye[ii][2] - VB->Eye[jj][2];
               dw = VB->Eye[ii][3] - VB->Eye[jj][3];
	       denom = dx*a + dy*b + dz*c + dw*d;
	       if (denom==0.0) {
		  t = 0.0;
	       }
	       else {
		  t = -(VB->Eye[jj][0]*a+VB->Eye[jj][1]*b
		       +VB->Eye[jj][2]*c+VB->Eye[jj][3]*d) / denom;
                  if (t>1.0F)  t = 1.0F;
	       }
	       VB->Eye[VB->Free][0] = VB->Eye[jj][0] + t * dx;
	       VB->Eye[VB->Free][1] = VB->Eye[jj][1] + t * dy;
	       VB->Eye[VB->Free][2] = VB->Eye[jj][2] + t * dz;
	       VB->Eye[VB->Free][3] = VB->Eye[jj][3] + t * dw;

	       /* Interpolate colors, indexes, and/or texture coords */
	       if (ctx->ClipMask)
		  interpolate_aux( ctx, EYE_SPACE, VB->Free, t, jj, ii );

	       ii = VB->Free;
	       VB->Free++;
	       if (VB->Free==VB_SIZE)   VB->Free = 1;
            }
         }
         else {
            if (OUTSIDE( jj, a,b,c,d )) {
               /* ii is inside, jj is outside ==> clip */
               GLfloat dx, dy, dz, dw, t, denom;
               dx = VB->Eye[jj][0] - VB->Eye[ii][0];
               dy = VB->Eye[jj][1] - VB->Eye[ii][1];
               dz = VB->Eye[jj][2] - VB->Eye[ii][2];
               dw = VB->Eye[jj][3] - VB->Eye[ii][3];
	       denom = dx*a + dy*b + dz*c + dw*d;
	       if (denom==0.0) {
		  t = 0.0;
	       }
	       else {
		  t = -(VB->Eye[ii][0]*a+VB->Eye[ii][1]*b
		       +VB->Eye[ii][2]*c+VB->Eye[ii][3]*d) / denom;
                  if (t>1.0F)  t = 1.0F;
	       }
	       VB->Eye[VB->Free][0] = VB->Eye[ii][0] + t * dx;
	       VB->Eye[VB->Free][1] = VB->Eye[ii][1] + t * dy;
	       VB->Eye[VB->Free][2] = VB->Eye[ii][2] + t * dz;
	       VB->Eye[VB->Free][3] = VB->Eye[ii][3] + t * dw;

	       /* Interpolate colors, indexes, and/or texture coords */
	       if (ctx->ClipMask)
		  interpolate_aux( ctx, EYE_SPACE, VB->Free, t, ii, jj );

	       jj = VB->Free;
	       VB->Free++;
	       if (VB->Free==VB_SIZE)   VB->Free = 1;
            }
            else {
               /* ii and jj inside ==> do nothing */
            }
         }
      }
   }

   *i = ii;
   *j = jj;
   return 1;
}