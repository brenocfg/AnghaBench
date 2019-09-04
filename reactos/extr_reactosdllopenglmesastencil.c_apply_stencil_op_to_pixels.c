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
 int* STENCIL_ADDRESS (size_t const,size_t const) ; 
 int /*<<< orphan*/  gl_problem (TYPE_2__*,char*) ; 

__attribute__((used)) static void apply_stencil_op_to_pixels( GLcontext *ctx,
                                        GLuint n, const GLint x[],
				        const GLint y[],
				        GLenum oper, GLubyte mask[] )
{
   GLint i;
   GLstencil ref;
   GLstencil wrtmask, invmask;

   wrtmask = ctx->Stencil.WriteMask;
   invmask = ~ctx->Stencil.WriteMask;

   ref = ctx->Stencil.Ref;

   switch (oper) {
      case GL_KEEP:
         /* do nothing */
         break;
      case GL_ZERO:
	 if (invmask==0) {
	    for (i=0;i<n;i++) {
	       if (mask[i]) {
                  GLstencil *sptr = STENCIL_ADDRESS( x[i], y[i] );
                  *sptr = 0;
	       }
	    }
	 }
	 else {
	    for (i=0;i<n;i++) {
	       if (mask[i]) {
                  GLstencil *sptr = STENCIL_ADDRESS( x[i], y[i] );
		  *sptr = invmask & *sptr;
	       }
	    }
	 }
	 break;
      case GL_REPLACE:
	 if (invmask==0) {
	    for (i=0;i<n;i++) {
	       if (mask[i]) {
                  GLstencil *sptr = STENCIL_ADDRESS( x[i], y[i] );
                  *sptr = ref;
	       }
	    }
	 }
	 else {
	    for (i=0;i<n;i++) {
	       if (mask[i]) {
                  GLstencil *sptr = STENCIL_ADDRESS( x[i], y[i] );
		  *sptr = (invmask & *sptr ) | (wrtmask & ref);
	       }
	    }
	 }
	 break;
      case GL_INCR:
	 if (invmask==0) {
	    for (i=0;i<n;i++) {
	       if (mask[i]) {
                  GLstencil *sptr = STENCIL_ADDRESS( x[i], y[i] );
		  if (*sptr < 0xff) {
		     *sptr = *sptr + 1;
		  }
	       }
	    }
	 }
	 else {
	    for (i=0;i<n;i++) {
	       if (mask[i]) {
                  GLstencil *sptr = STENCIL_ADDRESS( x[i], y[i] );
		  if (*sptr<0xff) {
		     *sptr = (invmask & *sptr) | (wrtmask & (*sptr+1));
		  }
	       }
	    }
	 }
	 break;
      case GL_DECR:
	 if (invmask==0) {
	    for (i=0;i<n;i++) {
	       if (mask[i]) {
                  GLstencil *sptr = STENCIL_ADDRESS( x[i], y[i] );
		  if (*sptr>0) {
		     *sptr = *sptr - 1;
		  }
	       }
	    }
	 }
	 else {
	    for (i=0;i<n;i++) {
	       if (mask[i]) {
                  GLstencil *sptr = STENCIL_ADDRESS( x[i], y[i] );
		  if (*sptr>0) {
		     *sptr = (invmask & *sptr) | (wrtmask & (*sptr-1));
		  }
	       }
	    }
	 }
	 break;
      case GL_INVERT:
	 if (invmask==0) {
	    for (i=0;i<n;i++) {
	       if (mask[i]) {
                  GLstencil *sptr = STENCIL_ADDRESS( x[i], y[i] );
                  *sptr = ~*sptr;
	       }
	    }
	 }
	 else {
	    for (i=0;i<n;i++) {
	       if (mask[i]) {
                  GLstencil *sptr = STENCIL_ADDRESS( x[i], y[i] );
                  *sptr = (invmask & *sptr) | (wrtmask & ~*sptr);
	       }
	    }
	 }
	 break;
      default:
         gl_problem(ctx, "Bad stencilop in apply_stencil_op_to_pixels");
   }
}