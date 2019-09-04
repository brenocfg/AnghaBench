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
struct TYPE_5__ {size_t IndexMask; } ;
struct TYPE_6__ {TYPE_1__ Color; } ;
typedef  size_t GLuint ;
typedef  int /*<<< orphan*/  GLint ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
 int MAX_WIDTH ; 
 int /*<<< orphan*/  gl_read_index_span (TYPE_2__*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 

void gl_mask_index_span( GLcontext *ctx,
                         GLuint n, GLint x, GLint y, GLuint index[] )
{
   GLuint i;
   GLuint fbindexes[MAX_WIDTH];
   GLuint msrc, mdest;

   gl_read_index_span( ctx, n, x, y, fbindexes );

   msrc = ctx->Color.IndexMask;
   mdest = ~msrc;

   for (i=0;i<n;i++) {
      index[i] = (index[i] & msrc) | (fbindexes[i] & mdest);
   }
}