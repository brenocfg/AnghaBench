#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {double DepthBias; double DepthScale; double ZoomX; double ZoomY; } ;
struct TYPE_12__ {int* RasterColor; size_t RasterIndex; scalar_t__* RasterPos; } ;
struct TYPE_14__ {TYPE_3__* Visual; TYPE_1__ Pixel; TYPE_2__ Current; } ;
struct TYPE_13__ {int RedScale; int GreenScale; int BlueScale; int AlphaScale; scalar_t__ RGBAflag; } ;
typedef  int /*<<< orphan*/  GLvoid ;
typedef  int /*<<< orphan*/  GLushort ;
typedef  size_t GLuint ;
typedef  int /*<<< orphan*/  GLubyte ;
typedef  size_t GLsizei ;
typedef  int /*<<< orphan*/  GLshort ;
typedef  scalar_t__ GLint ;
typedef  int GLfloat ;
typedef  int GLenum ;
typedef  size_t GLdepth ;
typedef  TYPE_4__ GLcontext ;
typedef  int /*<<< orphan*/  GLbyte ;
typedef  int GLboolean ;

/* Variables and functions */
 int BYTE_TO_FLOAT (int /*<<< orphan*/ ) ; 
 int CLAMP (int,float,float) ; 
 int DEPTH_SCALE ; 
 int /*<<< orphan*/  GL_BITMAP ; 
#define  GL_BYTE 134 
#define  GL_FLOAT 133 
#define  GL_INT 132 
#define  GL_SHORT 131 
#define  GL_UNSIGNED_BYTE 130 
#define  GL_UNSIGNED_INT 129 
#define  GL_UNSIGNED_SHORT 128 
 int INT_TO_FLOAT (int /*<<< orphan*/ ) ; 
 size_t MAX_DEPTH ; 
 int MAX_WIDTH ; 
 int /*<<< orphan*/  MEMSET (int /*<<< orphan*/ *,scalar_t__,size_t) ; 
 int SHORT_TO_FLOAT (int /*<<< orphan*/ ) ; 
 int UBYTE_TO_FLOAT (int /*<<< orphan*/ ) ; 
 int UINT_TO_FLOAT (int /*<<< orphan*/ ) ; 
 int USHORT_TO_FLOAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_problem (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  gl_write_color_span (TYPE_4__*,size_t,scalar_t__,scalar_t__,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_write_index_span (TYPE_4__*,size_t,scalar_t__,scalar_t__,size_t*,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_write_zoomed_color_span (TYPE_4__*,size_t,scalar_t__,scalar_t__,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  gl_write_zoomed_index_span (TYPE_4__*,size_t,scalar_t__,scalar_t__,size_t*,size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void draw_depth_pixels( GLcontext* ctx, GLsizei width, GLsizei height,
			       GLenum type, const GLvoid *pixels )
{
   GLint x, y, desty;
   GLubyte red[MAX_WIDTH], green[MAX_WIDTH], blue[MAX_WIDTH], alpha[MAX_WIDTH];
   GLuint ispan[MAX_WIDTH];
   GLboolean bias_or_scale;
   GLboolean zoom;

   bias_or_scale = ctx->Pixel.DepthBias!=0.0 || ctx->Pixel.DepthScale!=1.0;
   zoom = ctx->Pixel.ZoomX!=1.0 || ctx->Pixel.ZoomY!=1.0;

   /* Position, depth of pixels */
   x = (GLint) (ctx->Current.RasterPos[0] + 0.5F);
   y = (GLint) (ctx->Current.RasterPos[1] + 0.5F);
   desty = y;

   /* Color or index */
   if (ctx->Visual->RGBAflag) {
      GLint r, g, b, a;
      r = (GLint) (ctx->Current.RasterColor[0] * ctx->Visual->RedScale);
      g = (GLint) (ctx->Current.RasterColor[1] * ctx->Visual->GreenScale);
      b = (GLint) (ctx->Current.RasterColor[2] * ctx->Visual->BlueScale);
      a = (GLint) (ctx->Current.RasterColor[3] * ctx->Visual->AlphaScale);
      MEMSET( red,   r, width );
      MEMSET( green, g, width );
      MEMSET( blue,  b, width );
      MEMSET( alpha, a, width );
   }
   else {
      GLuint i;
      for (i=0;i<width;i++) {
	 ispan[i] = ctx->Current.RasterIndex;
      }
   }

   if (type==GL_UNSIGNED_INT && !bias_or_scale && !zoom && ctx->Visual->RGBAflag)
   {
      /* Special case: directly write 32-bit depth values */
      GLuint i, j;
      /* Compute shift value to scale 32-bit uints down to depth values. */
      GLuint shift = 0;
      GLuint max = MAX_DEPTH;
      while ((max&0x80000000)==0) {
         max = max << 1;
         shift++;
      }
      for (j=0;j<height;j++,y++) {
         GLdepth zspan[MAX_WIDTH];
         GLuint *zptr = (GLuint *) pixels + j * width;
         for (i=0;i<width;i++) {
            zspan[i] = zptr[i] >> shift;
         }
         gl_write_color_span( ctx, width, x, y, zspan,
                              red, green, blue, alpha, GL_BITMAP );
      }
   }
   else {
      /* General case (slower) */
      GLuint i, j;

      /* process image row by row */
      for (i=0;i<height;i++,y++) {
         GLfloat depth[MAX_WIDTH];
         GLdepth zspan[MAX_WIDTH];

         switch (type) {
            case GL_UNSIGNED_BYTE:
               {
                  GLubyte *src = (GLubyte *) pixels + i * width;
                  for (j=0;j<width;j++) {
                     depth[j] = UBYTE_TO_FLOAT( *src++ );
                  }
               }
               break;
            case GL_BYTE:
               {
                  GLbyte *src = (GLbyte *) pixels + i * width;
                  for (j=0;j<width;j++) {
                     depth[j] = BYTE_TO_FLOAT( *src++ );
                  }
               }
               break;
            case GL_UNSIGNED_SHORT:
               {
                  GLushort *src = (GLushort *) pixels + i * width;
                  for (j=0;j<width;j++) {
                     depth[j] = USHORT_TO_FLOAT( *src++ );
                  }
               }
               break;
            case GL_SHORT:
               {
                  GLshort *src = (GLshort *) pixels + i * width;
                  for (j=0;j<width;j++) {
                     depth[j] = SHORT_TO_FLOAT( *src++ );
                  }
               }
               break;
            case GL_UNSIGNED_INT:
               {
                  GLuint *src = (GLuint *) pixels + i * width;
                  for (j=0;j<width;j++) {
                     depth[j] = UINT_TO_FLOAT( *src++ );
                  }
               }
               break;
            case GL_INT:
               {
                  GLint *src = (GLint *) pixels + i * width;
                  for (j=0;j<width;j++) {
                     depth[j] = INT_TO_FLOAT( *src++ );
                  }
               }
               break;
            case GL_FLOAT:
               {
                  GLfloat *src = (GLfloat *) pixels + i * width;
                  for (j=0;j<width;j++) {
                     depth[j] = *src++;
                  }
               }
               break;
            default:
               gl_problem(ctx, "Bad type in draw_depth_pixels");
               return;
         }

         /* apply depth scale and bias */
         if (ctx->Pixel.DepthScale!=1.0 || ctx->Pixel.DepthBias!=0.0) {
            for (j=0;j<width;j++) {
               depth[j] = depth[j] * ctx->Pixel.DepthScale + ctx->Pixel.DepthBias;
            }
         }

         /* clamp depth values to [0,1] and convert from floats to integers */
         for (j=0;j<width;j++) {
            zspan[j] = (GLdepth) (CLAMP( depth[j], 0.0F, 1.0F ) * DEPTH_SCALE);
         }

         if (ctx->Visual->RGBAflag) {
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
            if (zoom) {
               gl_write_zoomed_index_span( ctx, width, x, y, zspan,
                                           ispan, GL_BITMAP );
            }
            else {
               gl_write_index_span( ctx, width, x, y, zspan, ispan, GL_BITMAP );
            }
         }

      }
   }
}