#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  (* WriteColorSpan ) (TYPE_8__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* SetBuffer ) (TYPE_8__*,scalar_t__) ;} ;
struct TYPE_17__ {scalar_t__ DrawBuffer; } ;
struct TYPE_20__ {float ZoomX; float ZoomY; double RedScale; double RedBias; double GreenScale; double GreenBias; double BlueScale; double BlueBias; double AlphaScale; double AlphaBias; scalar_t__ ReadBuffer; int MapRtoRsize; int MapGtoGsize; int MapBtoBsize; int MapAtoAsize; int* MapRtoR; int* MapGtoG; int* MapBtoB; int* MapAtoA; scalar_t__ MapColorFlag; } ;
struct TYPE_22__ {int* RasterPos; } ;
struct TYPE_21__ {scalar_t__ Test; } ;
struct TYPE_23__ {scalar_t__ RasterMask; TYPE_4__ Driver; TYPE_3__* Buffer; TYPE_2__ Color; TYPE_1__* Visual; TYPE_5__ Pixel; TYPE_7__ Current; TYPE_6__ Depth; } ;
struct TYPE_18__ {scalar_t__ Width; scalar_t__ Height; } ;
struct TYPE_16__ {scalar_t__ RedScale; scalar_t__ GreenScale; scalar_t__ BlueScale; scalar_t__ AlphaScale; int InvRedScale; int InvGreenScale; int InvBlueScale; int InvAlphaScale; } ;
typedef  scalar_t__ GLint ;
typedef  scalar_t__ GLfloat ;
typedef  TYPE_8__ GLcontext ;
typedef  int GLboolean ;

/* Variables and functions */
 scalar_t__ CLAMP (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  DEFARRAY (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int DEPTH_SCALE ; 
 int /*<<< orphan*/  GL_BITMAP ; 
 int GL_FALSE ; 
 int GL_TRUE ; 
 int /*<<< orphan*/  GLdepth ; 
 int /*<<< orphan*/  GLubyte ; 
 int /*<<< orphan*/  MAX_WIDTH ; 
 int /*<<< orphan*/  UNDEFARRAY (scalar_t__*) ; 
 scalar_t__* alpha ; 
 scalar_t__* blue ; 
 int /*<<< orphan*/  gl_read_color_span (TYPE_8__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  gl_write_color_span (TYPE_8__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_write_zoomed_color_span (TYPE_8__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__) ; 
 scalar_t__* green ; 
 scalar_t__* red ; 
 int /*<<< orphan*/  stub1 (TYPE_8__*,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (TYPE_8__*,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (TYPE_8__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__* zspan ; 

__attribute__((used)) static void copy_rgb_pixels( GLcontext* ctx,
                             GLint srcx, GLint srcy, GLint width, GLint height,
                             GLint destx, GLint desty )
{
   DEFARRAY( GLdepth, zspan, MAX_WIDTH );
   DEFARRAY( GLubyte, red, MAX_WIDTH );
   DEFARRAY( GLubyte, green, MAX_WIDTH );
   DEFARRAY( GLubyte, blue, MAX_WIDTH );
   DEFARRAY( GLubyte, alpha, MAX_WIDTH );
   GLboolean scale_or_bias, quick_draw, zoom;
   GLint sy, dy, stepy;
   GLint i, j;
   GLboolean setbuffer;

   if (ctx->Pixel.ZoomX==1.0F && ctx->Pixel.ZoomY==1.0F) {
      zoom = GL_FALSE;
   }
   else {
      zoom = GL_TRUE;
   }

   /* Determine if copy should be done bottom-to-top or top-to-bottom */
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

   scale_or_bias = ctx->Pixel.RedScale!=1.0 || ctx->Pixel.RedBias!=0.0
                || ctx->Pixel.GreenScale!=1.0 || ctx->Pixel.GreenBias!=0.0
		|| ctx->Pixel.BlueScale!=1.0 || ctx->Pixel.BlueBias!=0.0
		|| ctx->Pixel.AlphaScale!=1.0 || ctx->Pixel.AlphaBias!=0.0;

   if (ctx->Depth.Test) {
      /* fill in array of z values */
      GLint z = (GLint) (ctx->Current.RasterPos[2] * DEPTH_SCALE);
      for (i=0;i<width;i++) {
         zspan[i] = z;
      }
   }

   if (ctx->RasterMask==0 && !zoom
       && destx>=0 && destx+width<=ctx->Buffer->Width) {
      quick_draw = GL_TRUE;
   }
   else {
      quick_draw = GL_FALSE;
   }

   /* If read and draw buffer are different we must do buffer switching */
   setbuffer = ctx->Pixel.ReadBuffer!=ctx->Color.DrawBuffer;

   for (j=0; j<height; j++, sy+=stepy, dy+=stepy) {
      /* read */

      if (setbuffer) {
         (*ctx->Driver.SetBuffer)( ctx, ctx->Pixel.ReadBuffer );
      }
      gl_read_color_span( ctx, width, srcx, sy, red, green, blue, alpha );

      if (scale_or_bias) {
         GLfloat rbias = ctx->Pixel.RedBias   * ctx->Visual->RedScale;
         GLfloat gbias = ctx->Pixel.GreenBias * ctx->Visual->GreenScale;
         GLfloat bbias = ctx->Pixel.BlueBias  * ctx->Visual->BlueScale;
         GLfloat abias = ctx->Pixel.AlphaBias * ctx->Visual->AlphaScale;
         GLint rmax = (GLint) ctx->Visual->RedScale;
         GLint gmax = (GLint) ctx->Visual->GreenScale;
         GLint bmax = (GLint) ctx->Visual->BlueScale;
         GLint amax = (GLint) ctx->Visual->AlphaScale;
         for (i=0;i<width;i++) {
            GLint r = red[i]   * ctx->Pixel.RedScale   + rbias;
            GLint g = green[i] * ctx->Pixel.GreenScale + gbias;
            GLint b = blue[i]  * ctx->Pixel.BlueScale  + bbias;
            GLint a = alpha[i] * ctx->Pixel.AlphaScale + abias;
            red[i]   = CLAMP( r, 0, rmax );
            green[i] = CLAMP( g, 0, gmax );
            blue[i]  = CLAMP( b, 0, bmax );
            alpha[i] = CLAMP( a, 0, amax );
         }
      }

      if (ctx->Pixel.MapColorFlag) {
         GLfloat r = (ctx->Pixel.MapRtoRsize-1) * ctx->Visual->InvRedScale;
         GLfloat g = (ctx->Pixel.MapGtoGsize-1) * ctx->Visual->InvGreenScale;
         GLfloat b = (ctx->Pixel.MapBtoBsize-1) * ctx->Visual->InvBlueScale;
         GLfloat a = (ctx->Pixel.MapAtoAsize-1) * ctx->Visual->InvAlphaScale;
         for (i=0;i<width;i++) {
            GLint ir = red[i] * r;
            GLint ig = green[i] * g;
            GLint ib = blue[i] * b;
            GLint ia = alpha[i] * a;
            red[i]   = (GLint) (ctx->Pixel.MapRtoR[ir]*ctx->Visual->RedScale);
            green[i] = (GLint) (ctx->Pixel.MapGtoG[ig]*ctx->Visual->GreenScale);
            blue[i]  = (GLint) (ctx->Pixel.MapBtoB[ib]*ctx->Visual->BlueScale);
            alpha[i] = (GLint) (ctx->Pixel.MapAtoA[ia]*ctx->Visual->AlphaScale);
         }
      }

      /* write */
      if (setbuffer) {
         (*ctx->Driver.SetBuffer)( ctx, ctx->Color.DrawBuffer );
      }
      if (quick_draw && dy>=0 && dy<ctx->Buffer->Height) {
         (*ctx->Driver.WriteColorSpan)( ctx, width, destx, dy,
                                 red, green, blue, alpha, NULL);
      }
      else if (zoom) {
         gl_write_zoomed_color_span( ctx, width, destx, dy, zspan,
                                     red, green, blue, alpha, desty );
      }
      else {
         gl_write_color_span( ctx, width, destx, dy, zspan,
                              red, green, blue, alpha, GL_BITMAP );
      }
   }
   UNDEFARRAY( zspan );
   UNDEFARRAY( red );
   UNDEFARRAY( green );
   UNDEFARRAY( blue );
   UNDEFARRAY( alpha );
}