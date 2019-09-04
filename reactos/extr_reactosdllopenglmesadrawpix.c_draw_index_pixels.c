#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {double ZoomX; double ZoomY; size_t IndexOffset; size_t IndexShift; int* MapItoR; int* MapItoG; int* MapItoB; int* MapItoA; size_t* MapItoI; scalar_t__ MapColorFlag; } ;
struct TYPE_13__ {float* RasterPos; } ;
struct TYPE_12__ {scalar_t__ Test; } ;
struct TYPE_16__ {TYPE_3__ Pixel; TYPE_4__* Visual; TYPE_2__ Current; TYPE_1__ Depth; } ;
struct TYPE_15__ {int RedScale; int GreenScale; int BlueScale; int AlphaScale; scalar_t__ RGBAflag; } ;
typedef  int /*<<< orphan*/  GLvoid ;
typedef  int /*<<< orphan*/  GLushort ;
typedef  size_t GLuint ;
typedef  scalar_t__ GLubyte ;
typedef  size_t GLsizei ;
typedef  int /*<<< orphan*/  GLshort ;
typedef  scalar_t__ GLint ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  int GLenum ;
typedef  int /*<<< orphan*/  GLdepth ;
typedef  TYPE_5__ GLcontext ;
typedef  int /*<<< orphan*/  GLbyte ;
typedef  int GLboolean ;

/* Variables and functions */
 int DEPTH_SCALE ; 
#define  GL_BITMAP 135 
#define  GL_BYTE 134 
#define  GL_FLOAT 133 
#define  GL_INT 132 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
#define  GL_SHORT 131 
#define  GL_UNSIGNED_BYTE 130 
#define  GL_UNSIGNED_INT 129 
#define  GL_UNSIGNED_SHORT 128 
 int MAX_WIDTH ; 
 int /*<<< orphan*/  gl_error (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gl_write_color_span (TYPE_5__*,size_t,scalar_t__,scalar_t__,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,int const) ; 
 int /*<<< orphan*/  gl_write_index_span (TYPE_5__*,size_t,scalar_t__,scalar_t__,int /*<<< orphan*/ *,size_t*,int const) ; 
 int /*<<< orphan*/  gl_write_zoomed_color_span (TYPE_5__*,size_t,scalar_t__,scalar_t__,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  gl_write_zoomed_index_span (TYPE_5__*,size_t,scalar_t__,scalar_t__,int /*<<< orphan*/ *,size_t*,scalar_t__) ; 

__attribute__((used)) static void draw_index_pixels( GLcontext* ctx, GLsizei width, GLsizei height,
			       GLenum type, const GLvoid *pixels )
{
   GLint x, y, desty;
   GLuint i, j;
   GLdepth zspan[MAX_WIDTH];
   GLboolean zoom;

   zoom = ctx->Pixel.ZoomX!=1.0 || ctx->Pixel.ZoomY!=1.0;

   /* Position, depth of pixels */
   x = (GLint) (ctx->Current.RasterPos[0] + 0.5F);
   y = (GLint) (ctx->Current.RasterPos[1] + 0.5F);
   desty = y;
   if (ctx->Depth.Test) {
      GLdepth zval = (GLdepth) (ctx->Current.RasterPos[2] * DEPTH_SCALE);
      for (i=0;i<width;i++) {
	 zspan[i] = zval;
      }
   }

   /* process the image row by row */
   for (i=0;i<height;i++,y++) {
      GLuint ispan[MAX_WIDTH];

      /* convert to uints */
      switch (type) {
	 case GL_UNSIGNED_BYTE:
	    {
	       GLubyte *src = (GLubyte *) pixels + i * width;
	       for (j=0;j<width;j++) {
		  ispan[j] = (GLuint) *src++;
	       }
	    }
	    break;
	 case GL_BYTE:
	    {
	       GLbyte *src = (GLbyte *) pixels + i * width;
	       for (j=0;j<width;j++) {
		  ispan[j] = (GLuint) *src++;
	       }
	    }
	    break;
	 case GL_UNSIGNED_SHORT:
	    {
	       GLushort *src = (GLushort *) pixels + i * width;
	       for (j=0;j<width;j++) {
		  ispan[j] = (GLuint) *src++;
	       }
	    }
	    break;
	 case GL_SHORT:
	    {
	       GLshort *src = (GLshort *) pixels + i * width;
	       for (j=0;j<width;j++) {
		  ispan[j] = (GLuint) *src++;
	       }
	    }
	    break;
	 case GL_UNSIGNED_INT:
	    {
	       GLuint *src = (GLuint *) pixels + i * width;
	       for (j=0;j<width;j++) {
		  ispan[j] = *src++;
	       }
	    }
	    break;
	 case GL_INT:
	    {
	       GLint *src = (GLint *) pixels + i * width;
	       for (j=0;j<width;j++) {
		  ispan[j] = (GLuint) *src++;
	       }
	    }
	    break;
	 case GL_BITMAP:
	    /* TODO */
	    break;
	 case GL_FLOAT:
	    {
	       GLfloat *src = (GLfloat *) pixels + i * width;
	       for (j=0;j<width;j++) {
		  ispan[j] = (GLuint) (GLint) *src++;
	       }
	    }
	    break;
	 default:
	    gl_error( ctx, GL_INVALID_ENUM, "Internal: draw_index_pixels" );
      }

      /* apply shift and offset */
      if (ctx->Pixel.IndexOffset || ctx->Pixel.IndexShift) {
	 if (ctx->Pixel.IndexShift>=0) {
	    for (j=0;j<width;j++) {
	       ispan[j] = (ispan[j] << ctx->Pixel.IndexShift)
		          + ctx->Pixel.IndexOffset;
	    }
	 }
	 else {
	    for (j=0;j<width;j++) {
	       ispan[j] = (ispan[j] >> -ctx->Pixel.IndexShift)
		          + ctx->Pixel.IndexOffset;
	    }
	 }
      }

      if (ctx->Visual->RGBAflag) {
	 /* Convert index to RGBA and write to frame buffer */
	 GLubyte red[MAX_WIDTH], green[MAX_WIDTH];
	 GLubyte blue[MAX_WIDTH], alpha[MAX_WIDTH];
	 for (j=0;j<width;j++) {
	    red[j]   = (GLint) (ctx->Pixel.MapItoR[ispan[j]] * ctx->Visual->RedScale);
	    green[j] = (GLint) (ctx->Pixel.MapItoG[ispan[j]] * ctx->Visual->GreenScale);
	    blue[j]  = (GLint) (ctx->Pixel.MapItoB[ispan[j]] * ctx->Visual->BlueScale);
	    alpha[j] = (GLint) (ctx->Pixel.MapItoA[ispan[j]] * ctx->Visual->AlphaScale);
	 }
         if (zoom) {
            gl_write_zoomed_color_span( ctx, width, x, y, zspan,
                                        red, green, blue, alpha, desty );
         }
         else {
            gl_write_color_span( ctx, width, x, y, zspan,
                                 red, green, blue, alpha, GL_BITMAP );
         }
      }
      else {
	 /* optionally apply index map then write to frame buffer */
	 if (ctx->Pixel.MapColorFlag) {
	    for (j=0;j<width;j++) {
	       ispan[j] = ctx->Pixel.MapItoI[ispan[j]];
	    }
	 }
         if (zoom) {
            gl_write_zoomed_index_span( ctx, width, x, y, zspan, ispan, desty );
         }
         else {
            gl_write_index_span( ctx, width, x, y, zspan, ispan, GL_BITMAP );
         }
      }
   }

}