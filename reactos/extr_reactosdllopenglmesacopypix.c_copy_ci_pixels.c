#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ DrawBuffer; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* SetBuffer ) (TYPE_6__*,scalar_t__) ;} ;
struct TYPE_15__ {float ZoomX; float ZoomY; scalar_t__ ReadBuffer; size_t IndexShift; size_t IndexOffset; size_t MapItoIsize; size_t* MapItoI; scalar_t__ MapColorFlag; } ;
struct TYPE_14__ {int* RasterPos; } ;
struct TYPE_13__ {scalar_t__ Test; } ;
struct TYPE_18__ {TYPE_5__ Color; TYPE_4__ Driver; TYPE_3__ Pixel; TYPE_2__ Current; TYPE_1__ Depth; } ;
typedef  size_t GLuint ;
typedef  size_t GLint ;
typedef  size_t GLdepth ;
typedef  TYPE_6__ GLcontext ;
typedef  int GLboolean ;

/* Variables and functions */
 int DEPTH_SCALE ; 
 int /*<<< orphan*/  GL_BITMAP ; 
 int GL_FALSE ; 
 int GL_TRUE ; 
 int MAX_WIDTH ; 
 int /*<<< orphan*/  gl_read_index_span (TYPE_6__*,size_t,size_t,size_t,size_t*) ; 
 int /*<<< orphan*/  gl_write_index_span (TYPE_6__*,size_t,size_t,size_t,size_t*,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_write_zoomed_index_span (TYPE_6__*,size_t,size_t,size_t,size_t*,size_t*,size_t) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (TYPE_6__*,scalar_t__) ; 

__attribute__((used)) static void copy_ci_pixels( GLcontext* ctx,
                            GLint srcx, GLint srcy, GLint width, GLint height,
                            GLint destx, GLint desty )
{
   GLdepth zspan[MAX_WIDTH];
   GLuint indx[MAX_WIDTH];
   GLint sy, dy, stepy;
   GLint i, j;
   GLboolean setbuffer, zoom;

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

   if (ctx->Depth.Test) {
      /* fill in array of z values */
      GLint z = (GLint) (ctx->Current.RasterPos[2] * DEPTH_SCALE);
      for (i=0;i<width;i++) {
         zspan[i] = z;
      }
   }

   /* If read and draw buffer are different we must do buffer switching */
   setbuffer = ctx->Pixel.ReadBuffer!=ctx->Color.DrawBuffer;

   for (j=0; j<height; j++, sy+=stepy, dy+=stepy) {
      /* read */
      if (setbuffer) {
         (*ctx->Driver.SetBuffer)( ctx, ctx->Pixel.ReadBuffer );
      }
      gl_read_index_span( ctx, width, srcx, sy, indx );

      /* shift, offset */
      if (ctx->Pixel.IndexShift || ctx->Pixel.IndexOffset) {
         if (ctx->Pixel.IndexShift<0) {
            for (i=0;i<width;i++) {
               indx[i] = (indx[i] >> -ctx->Pixel.IndexShift)
                         + ctx->Pixel.IndexOffset;
            }
         }
         else {
            for (i=0;i<width;i++) {
               indx[i] = (indx[i] << ctx->Pixel.IndexShift)
                         + ctx->Pixel.IndexOffset;
            }
         }
      }

      /* mapping */
      if (ctx->Pixel.MapColorFlag) {
         for (i=0;i<width;i++) {
            if (indx[i] < ctx->Pixel.MapItoIsize) {
               indx[i] = ctx->Pixel.MapItoI[ indx[i] ];
            }
         }
      }

      /* write */
      if (setbuffer) {
         (*ctx->Driver.SetBuffer)( ctx, ctx->Color.DrawBuffer );
      }
      if (zoom) {
         gl_write_zoomed_index_span( ctx, width, destx, dy, zspan, indx, desty );
      }
      else {
         gl_write_index_span( ctx, width, destx, dy, zspan, indx, GL_BITMAP );
      }
   }
}