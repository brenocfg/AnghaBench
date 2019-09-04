#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t IndexMask; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* ReadIndexPixels ) (TYPE_3__*,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t*,int /*<<< orphan*/  const*) ;} ;
struct TYPE_8__ {TYPE_1__ Color; TYPE_2__ Driver; } ;
typedef  size_t GLuint ;
typedef  int /*<<< orphan*/  GLubyte ;
typedef  int /*<<< orphan*/  GLint ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 int PB_SIZE ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t*,int /*<<< orphan*/  const*) ; 

void gl_mask_index_pixels( GLcontext *ctx,
                           GLuint n, const GLint x[], const GLint y[],
                           GLuint index[], const GLubyte mask[] )
{
   GLuint i;
   GLuint fbindexes[PB_SIZE];
   GLuint msrc, mdest;

   (*ctx->Driver.ReadIndexPixels)( ctx, n, x, y, fbindexes, mask );

   msrc = ctx->Color.IndexMask;
   mdest = ~msrc;

   for (i=0;i<n;i++) {
      index[i] = (index[i] & msrc) | (fbindexes[i] & mdest);
   }
}