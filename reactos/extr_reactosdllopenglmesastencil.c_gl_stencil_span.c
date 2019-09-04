#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int Function; int Ref; int ValueMask; int /*<<< orphan*/  FailFunc; } ;
struct TYPE_7__ {TYPE_1__ Stencil; } ;
typedef  size_t GLuint ;
typedef  int GLubyte ;
typedef  int GLstencil ;
typedef  int GLint ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
#define  GL_ALWAYS 135 
#define  GL_EQUAL 134 
#define  GL_GEQUAL 133 
#define  GL_GREATER 132 
#define  GL_LEQUAL 131 
#define  GL_LESS 130 
#define  GL_NEVER 129 
#define  GL_NOTEQUAL 128 
 int MAX_WIDTH ; 
 int* STENCIL_ADDRESS (int,int) ; 
 int /*<<< orphan*/  apply_stencil_op_to_span (TYPE_2__*,size_t,int,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  gl_problem (TYPE_2__*,char*) ; 

GLint gl_stencil_span( GLcontext *ctx,
                       GLuint n, GLint x, GLint y, GLubyte mask[] )
{
   GLubyte fail[MAX_WIDTH];
   GLint allfail = 0;
   GLuint i;
   GLstencil r, s;
   GLstencil *stencil;

   stencil = STENCIL_ADDRESS( x, y );

   /*
    * Perform stencil test.  The results of this operation are stored
    * in the fail[] array:
    *   IF fail[i] is non-zero THEN
    *       the stencil fail operator is to be applied
    *   ELSE
    *       the stencil fail operator is not to be applied
    *   ENDIF
    */
   switch (ctx->Stencil.Function) {
      case GL_NEVER:
         /* always fail */
         for (i=0;i<n;i++) {
	    if (mask[i]) {
	       mask[i] = 0;
	       fail[i] = 1;
	    }
	    else {
	       fail[i] = 0;
	    }
	 }
	 allfail = 1;
	 break;
      case GL_LESS:
	 r = ctx->Stencil.Ref & ctx->Stencil.ValueMask;
	 for (i=0;i<n;i++) {
	    if (mask[i]) {
	       s = stencil[i] & ctx->Stencil.ValueMask;
	       if (r < s) {
		  /* passed */
		  fail[i] = 0;
	       }
	       else {
		  fail[i] = 1;
		  mask[i] = 0;
	       }
	    }
	    else {
	       fail[i] = 0;
	    }
	 }
	 break;
      case GL_LEQUAL:
	 r = ctx->Stencil.Ref & ctx->Stencil.ValueMask;
	 for (i=0;i<n;i++) {
	    if (mask[i]) {
	       s = stencil[i] & ctx->Stencil.ValueMask;
	       if (r <= s) {
		  /* pass */
		  fail[i] = 0;
	       }
	       else {
		  fail[i] = 1;
		  mask[i] = 0;
	       }
	    }
	    else {
	       fail[i] = 0;
	    }
	 }
	 break;
      case GL_GREATER:
	 r = ctx->Stencil.Ref & ctx->Stencil.ValueMask;
	 for (i=0;i<n;i++) {
	    if (mask[i]) {
	       s = stencil[i] & ctx->Stencil.ValueMask;
	       if (r > s) {
		  /* passed */
		  fail[i] = 0;
	       }
	       else {
		  fail[i] = 1;
		  mask[i] = 0;
	       }
	    }
	    else {
	       fail[i] = 0;
	    }
	 }
	 break;
      case GL_GEQUAL:
	 r = ctx->Stencil.Ref & ctx->Stencil.ValueMask;
	 for (i=0;i<n;i++) {
	    if (mask[i]) {
	       s = stencil[i] & ctx->Stencil.ValueMask;
	       if (r >= s) {
		  /* passed */
		  fail[i] = 0;
	       }
	       else {
		  fail[i] = 1;
		  mask[i] = 0;
	       }
	    }
	    else {
	       fail[i] = 0;
	    }
	 }
	 break;
      case GL_EQUAL:
	 r = ctx->Stencil.Ref & ctx->Stencil.ValueMask;
	 for (i=0;i<n;i++) {
	    if (mask[i]) {
	       s = stencil[i] & ctx->Stencil.ValueMask;
	       if (r == s) {
		  /* passed */
		  fail[i] = 0;
	       }
	       else {
		  fail[i] = 1;
		  mask[i] = 0;
	       }
	    }
	    else {
	       fail[i] = 0;
	    }
	 }
	 break;
      case GL_NOTEQUAL:
	 r = ctx->Stencil.Ref & ctx->Stencil.ValueMask;
	 for (i=0;i<n;i++) {
	    if (mask[i]) {
	       s = stencil[i] & ctx->Stencil.ValueMask;
	       if (r != s) {
		  /* passed */
		  fail[i] = 0;
	       }
	       else {
		  fail[i] = 1;
		  mask[i] = 0;
	       }
	    }
	    else {
	       fail[i] = 0;
	    }
	 }
	 break;
      case GL_ALWAYS:
	 /* always pass */
	 for (i=0;i<n;i++) {
	    fail[i] = 0;
	 }
	 break;
      default:
         gl_problem(ctx, "Bad stencil func in gl_stencil_span");
         return 0;
   }

   apply_stencil_op_to_span( ctx, n, x, y, ctx->Stencil.FailFunc, fail );

   return (allfail) ? 0 : 1;
}