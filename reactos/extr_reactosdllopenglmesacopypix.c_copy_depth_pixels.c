#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {float ZoomX; float ZoomY; int DepthScale; int DepthBias; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* ReadDepthSpanFloat ) (TYPE_6__*,size_t,size_t,size_t,int*) ;} ;
struct TYPE_15__ {int /*<<< orphan*/  Index; scalar_t__* ByteColor; } ;
struct TYPE_19__ {TYPE_5__* Visual; TYPE_4__ Pixel; TYPE_3__ Driver; TYPE_2__ Current; TYPE_1__* Buffer; } ;
struct TYPE_18__ {scalar_t__ RGBAflag; } ;
struct TYPE_14__ {int /*<<< orphan*/  Depth; } ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  scalar_t__ GLubyte ;
typedef  size_t GLint ;
typedef  int GLfloat ;
typedef  size_t GLdepth ;
typedef  TYPE_6__ GLcontext ;
typedef  scalar_t__ GLboolean ;

/* Variables and functions */
 int CLAMP (int,double,double) ; 
 int DEPTH_SCALE ; 
 int /*<<< orphan*/  GL_BITMAP ; 
 scalar_t__ GL_FALSE ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
 scalar_t__ GL_TRUE ; 
 int MAX_WIDTH ; 
 int /*<<< orphan*/  MEMSET (scalar_t__*,int,size_t) ; 
 int /*<<< orphan*/  gl_error (TYPE_6__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gl_write_color_span (TYPE_6__*,size_t,size_t,size_t,size_t*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_write_index_span (TYPE_6__*,size_t,size_t,size_t,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_write_zoomed_color_span (TYPE_6__*,size_t,size_t,size_t,size_t*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,size_t) ; 
 int /*<<< orphan*/  gl_write_zoomed_index_span (TYPE_6__*,size_t,size_t,size_t,size_t*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,size_t,size_t,size_t,int*) ; 

__attribute__((used)) static void copy_depth_pixels( GLcontext* ctx, GLint srcx, GLint srcy,
                               GLint width, GLint height,
                               GLint destx, GLint desty )
{
   GLfloat depth[MAX_WIDTH];
   GLdepth zspan[MAX_WIDTH];
   GLuint indx[MAX_WIDTH];
   GLubyte red[MAX_WIDTH], green[MAX_WIDTH];
   GLubyte blue[MAX_WIDTH], alpha[MAX_WIDTH];
   GLint sy, dy, stepy;
   GLint i, j;
   GLboolean zoom;

   if (!ctx->Buffer->Depth) {
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

   /* setup colors or indexes */
   if (ctx->Visual->RGBAflag) {
      GLubyte r, g, b, a;
      r = ctx->Current.ByteColor[0];
      g = ctx->Current.ByteColor[1];
      b = ctx->Current.ByteColor[2];
      a = ctx->Current.ByteColor[3];
      MEMSET( red,   (int) r, width );
      MEMSET( green, (int) g, width );
      MEMSET( blue,  (int) b, width );
      MEMSET( alpha, (int) a, width );
   }
   else {
      for (i=0;i<width;i++) {
         indx[i] = ctx->Current.Index;
      }
   }

   for (j=0; j<height; j++, sy+=stepy, dy+=stepy) {
      /* read */
      (*ctx->Driver.ReadDepthSpanFloat)( ctx, width, srcx, sy, depth );
      /* scale, bias, clamp */
      for (i=0;i<width;i++) {
         GLfloat d = depth[i] * ctx->Pixel.DepthScale + ctx->Pixel.DepthBias;
         zspan[i] = (GLint) (CLAMP( d, 0.0, 1.0 ) * DEPTH_SCALE);
      }
      /* write */
      if (ctx->Visual->RGBAflag) {
         if (zoom) {
            gl_write_zoomed_color_span( ctx, width, destx, dy, zspan,
                                        red, green, blue, alpha, desty );
         }
         else {
            gl_write_color_span( ctx, width, destx, dy, zspan,
                                 red, green, blue, alpha, GL_BITMAP );
         }
      }
      else {
         if (zoom) {
            gl_write_zoomed_index_span( ctx, width, destx, dy,
                                        zspan, indx, desty);
         }
         else {
            gl_write_index_span( ctx, width, destx, dy,
                                 zspan, indx, GL_BITMAP );
         }
      }
   }
}