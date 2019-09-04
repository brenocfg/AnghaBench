#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {float ZoomX; float ZoomY; size_t IndexShift; size_t IndexOffset; scalar_t__ MapStoSsize; size_t* MapStoS; scalar_t__ MapStencilFlag; } ;
struct TYPE_11__ {TYPE_2__ Pixel; TYPE_1__* Buffer; } ;
struct TYPE_9__ {int /*<<< orphan*/  Stencil; } ;
typedef  size_t GLubyte ;
typedef  scalar_t__ GLint ;
typedef  TYPE_3__ GLcontext ;
typedef  scalar_t__ GLboolean ;

/* Variables and functions */
 scalar_t__ GL_FALSE ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
 scalar_t__ GL_TRUE ; 
 int MAX_WIDTH ; 
 int /*<<< orphan*/  gl_error (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gl_read_stencil_span (TYPE_3__*,scalar_t__,scalar_t__,scalar_t__,size_t*) ; 
 int /*<<< orphan*/  gl_write_stencil_span (TYPE_3__*,scalar_t__,scalar_t__,scalar_t__,size_t*) ; 
 int /*<<< orphan*/  gl_write_zoomed_stencil_span (TYPE_3__*,scalar_t__,scalar_t__,scalar_t__,size_t*,scalar_t__) ; 

__attribute__((used)) static void copy_stencil_pixels( GLcontext* ctx, GLint srcx, GLint srcy,
                                 GLint width, GLint height,
                                 GLint destx, GLint desty )
{
   GLubyte stencil[MAX_WIDTH];
   GLint sy, dy, stepy;
   GLint i, j;
   GLboolean zoom;

   if (!ctx->Buffer->Stencil) {
      gl_error( ctx, GL_INVALID_OPERATION, "glCopyPixels" );
      return;
   }

   if (ctx->Pixel.ZoomX==1.0F && ctx->Pixel.ZoomY==1.0F) {
      zoom = GL_FALSE;
   }
   else {
      zoom = GL_TRUE;
   }

   /* Determine if copy should be bottom-to-top or top-to-bottom */
   if (srcy<desty) {
      /* top-down  max-to-min */
      sy = srcy + height - 1;
      dy = desty + height - 1;
      stepy = -1;
   }
   else {
      /* bottom-up  min-to-max */
      sy = srcy;
      dy = desty;
      stepy = 1;
   }

   for (j=0; j<height; j++, sy+=stepy, dy+=stepy) {
      /* read */
      gl_read_stencil_span( ctx, width, srcx, sy, stencil );
      /* shift, offset */
      if (ctx->Pixel.IndexShift<0) {
         for (i=0;i<width;i++) {
            stencil[i] = (stencil[i] >> -ctx->Pixel.IndexShift)
                         + ctx->Pixel.IndexOffset;
         }
      }
      else {
         for (i=0;i<width;i++) {
            stencil[i] = (stencil[i] << ctx->Pixel.IndexShift)
			 + ctx->Pixel.IndexOffset;
         }
      }
      /* mapping */
      if (ctx->Pixel.MapStencilFlag) {
         for (i=0;i<width;i++) {
            if ((GLint) stencil[i] < ctx->Pixel.MapStoSsize) {
               stencil[i] = ctx->Pixel.MapStoS[ stencil[i] ];
            }
         }
      }
      /* write */
      if (zoom) {
         gl_write_zoomed_stencil_span( ctx, width, destx, dy, stencil, desty );
      }
      else {
         gl_write_stencil_span( ctx, width, destx, dy, stencil );
      }
   }
}