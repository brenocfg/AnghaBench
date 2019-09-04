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
struct TYPE_5__ {int WriteMask; int Ref; } ;
struct TYPE_6__ {TYPE_1__ Stencil; } ;
typedef  size_t GLuint ;
typedef  int /*<<< orphan*/  GLubyte ;
typedef  int GLstencil ;
typedef  size_t GLint ;
typedef  int GLenum ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
#define  GL_DECR 133 
#define  GL_INCR 132 
#define  GL_INVERT 131 
#define  GL_KEEP 130 
#define  GL_REPLACE 129 
#define  GL_ZERO 128 
 int* STENCIL_ADDRESS (size_t,size_t) ; 
 int /*<<< orphan*/  gl_problem (TYPE_2__*,char*) ; 

__attribute__((used)) static void apply_stencil_op_to_span( GLcontext *ctx,
                                      GLuint n, GLint x, GLint y,
				      GLenum oper, GLubyte mask[] )
{
   GLint i;
   GLstencil s, ref;
   GLstencil wrtmask, invmask;
   GLstencil *stencil;

   wrtmask = ctx->Stencil.WriteMask;
   invmask = ~ctx->Stencil.WriteMask;
   ref = ctx->Stencil.Ref;
   stencil = STENCIL_ADDRESS( x, y );

   switch (oper) {
      case GL_KEEP:
         /* do nothing */
         break;
      case GL_ZERO:
	 if (invmask==0) {
	    for (i=0;i<n;i++) {
	       if (mask[i]) {
		  stencil[i] = 0;
	       }
	    }
	 }
	 else {
	    for (i=0;i<n;i++) {
	       if (mask[i]) {
		  stencil[i] = stencil[i] & invmask;
	       }
	    }
	 }
	 break;
      case GL_REPLACE:
	 if (invmask==0) {
	    for (i=0;i<n;i++) {
	       if (mask[i]) {
                  stencil[i] = ref;
	       }
	    }
	 }
	 else {
	    for (i=0;i<n;i++) {
	       if (mask[i]) {
		  s = stencil[i];
		  stencil[i] = (invmask & s ) | (wrtmask & ref);
	       }
	    }
	 }
	 break;
      case GL_INCR:
	 if (invmask==0) {
	    for (i=0;i<n;i++) {
	       if (mask[i]) {
		  s = stencil[i];
		  if (s<0xff) {
		     stencil[i] = s+1;
		  }
	       }
	    }
	 }
	 else {
	    for (i=0;i<n;i++) {
	       if (mask[i]) {
		  /* VERIFY logic of adding 1 to a write-masked value */
		  s = stencil[i];
		  if (s<0xff) {
		     stencil[i] = (invmask & s) | (wrtmask & (s+1));
		  }
	       }
	    }
	 }
	 break;
      case GL_DECR:
	 if (invmask==0) {
	    for (i=0;i<n;i++) {
	       if (mask[i]) {
		  s = stencil[i];
		  if (s>0) {
		     stencil[i] = s-1;
		  }
	       }
	    }
	 }
	 else {
	    for (i=0;i<n;i++) {
	       if (mask[i]) {
		  /* VERIFY logic of subtracting 1 to a write-masked value */
		  s = stencil[i];
		  if (s>0) {
		     stencil[i] = (invmask & s) | (wrtmask & (s-1));
		  }
	       }
	    }
	 }
	 break;
      case GL_INVERT:
	 if (invmask==0) {
	    for (i=0;i<n;i++) {
	       if (mask[i]) {
		  s = stencil[i];
		  stencil[i] = ~s;
	       }
	    }
	 }
	 else {
	    for (i=0;i<n;i++) {
	       if (mask[i]) {
		  s = stencil[i];
		  stencil[i] = (invmask & s) | (wrtmask & ~s);
	       }
	    }
	 }
	 break;
      default:
         gl_problem(ctx, "Bad stencilop in apply_stencil_op_to_span");
   }
}