#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  (* ReadIndexSpan ) (TYPE_3__*,size_t,scalar_t__,scalar_t__,size_t*) ;} ;
struct TYPE_9__ {TYPE_2__ Driver; TYPE_1__* Buffer; } ;
struct TYPE_7__ {scalar_t__ Height; scalar_t__ Width; } ;
typedef  size_t GLuint ;
typedef  scalar_t__ GLint ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 size_t MIN2 (size_t,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,size_t,scalar_t__,scalar_t__,size_t*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,size_t,scalar_t__,scalar_t__,size_t*) ; 

void gl_read_index_span( GLcontext *ctx,
                         GLuint n, GLint x, GLint y, GLuint indx[] )
{
   register GLuint i;

   if (y<0 || y>=ctx->Buffer->Height || x>=ctx->Buffer->Width) {
      /* completely above, below, or right */
      for (i=0;i<n;i++) {
	 indx[i] = 0;
      }
   }
   else {
      if (x>=0 && x+n<=ctx->Buffer->Width) {
	 /* OK */
	 (*ctx->Driver.ReadIndexSpan)( ctx, n, x, y, indx );
      }
      else {
	 i = 0;
	 if (x<0) {
	    while (x<0 && n>0) {
	       indx[i] = 0;
	       x++;
	       n--;
	       i++;
	    }
	 }
	 n = MIN2( n, ctx->Buffer->Width - x );
	 (*ctx->Driver.ReadIndexSpan)( ctx, n, x, y, indx+i );
      }
   }
}