#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_25__ {int Enabled; scalar_t__ EnvMode; TYPE_8__* Current1D; TYPE_7__* Current2D; TYPE_1__* Current; } ;
struct TYPE_24__ {scalar_t__ MinFilter; scalar_t__ MagFilter; } ;
struct TYPE_23__ {scalar_t__ MinFilter; scalar_t__ MagFilter; scalar_t__ WrapS; scalar_t__ WrapT; TYPE_2__** Image; } ;
struct TYPE_22__ {scalar_t__ EightBitColor; scalar_t__ RGBAflag; } ;
struct TYPE_21__ {scalar_t__ StippleFlag; } ;
struct TYPE_20__ {scalar_t__ Func; scalar_t__ Mask; } ;
struct TYPE_19__ {scalar_t__ PerspectiveCorrection; } ;
struct TYPE_18__ {scalar_t__ Format; scalar_t__ Border; } ;
struct TYPE_17__ {scalar_t__ Complete; } ;
struct TYPE_15__ {scalar_t__ TriangleFunc; } ;
struct TYPE_14__ {scalar_t__ ShadeModel; } ;
struct TYPE_16__ {scalar_t__ RenderMode; scalar_t__ TextureMatrixType; scalar_t__ RasterMask; TYPE_11__ Driver; TYPE_10__ Light; TYPE_9__ Texture; TYPE_6__* Visual; TYPE_5__ Polygon; TYPE_4__ Depth; TYPE_3__ Hint; scalar_t__ NoRaster; } ;
typedef  TYPE_12__ GLcontext ;
typedef  scalar_t__ GLboolean ;

/* Variables and functions */
 scalar_t__ DEPTH_BIT ; 
 scalar_t__ GL_DECAL ; 
 scalar_t__ GL_FALSE ; 
 scalar_t__ GL_FASTEST ; 
 scalar_t__ GL_FEEDBACK ; 
 scalar_t__ GL_LESS ; 
 scalar_t__ GL_NEAREST ; 
 scalar_t__ GL_RENDER ; 
 scalar_t__ GL_REPEAT ; 
 scalar_t__ GL_REPLACE ; 
 scalar_t__ GL_RGB ; 
 scalar_t__ GL_SMOOTH ; 
 scalar_t__ GL_TRUE ; 
 scalar_t__ MATRIX_IDENTITY ; 
 int TEXTURE_1D ; 
 int TEXTURE_2D ; 
 scalar_t__ feedback_triangle ; 
 scalar_t__ flat_ci_triangle ; 
 scalar_t__ flat_rgba_triangle ; 
 scalar_t__ general_textured_triangle ; 
 scalar_t__ lambda_textured_triangle ; 
 scalar_t__ null_triangle ; 
 scalar_t__ select_triangle ; 
 scalar_t__ simple_textured_triangle ; 
 scalar_t__ simple_z_textured_triangle ; 
 scalar_t__ smooth_ci_triangle ; 
 scalar_t__ smooth_rgba_triangle ; 

void gl_set_triangle_function( GLcontext *ctx )
{
   GLboolean rgbmode = ctx->Visual->RGBAflag;

   if (ctx->RenderMode==GL_RENDER) {
      if (ctx->NoRaster) {
         ctx->Driver.TriangleFunc = null_triangle;
         return;
      }
      if (ctx->Driver.TriangleFunc) {
         /* Device driver will draw triangles. */
      }
      else if (ctx->Texture.Enabled
               && ctx->Texture.Current
               && ctx->Texture.Current->Complete) {
         if (   (ctx->Texture.Enabled==TEXTURE_2D)
             && ctx->Texture.Current2D->MinFilter==GL_NEAREST
             && ctx->Texture.Current2D->MagFilter==GL_NEAREST
             && ctx->Texture.Current2D->WrapS==GL_REPEAT
             && ctx->Texture.Current2D->WrapT==GL_REPEAT
             && ctx->Texture.Current2D->Image[0]->Format==GL_RGB
             && ctx->Texture.Current2D->Image[0]->Border==0
             && (ctx->Texture.EnvMode==GL_DECAL
                 || ctx->Texture.EnvMode==GL_REPLACE)
             && ctx->Hint.PerspectiveCorrection==GL_FASTEST
             && ctx->TextureMatrixType==MATRIX_IDENTITY
             && ((ctx->RasterMask==DEPTH_BIT
                  && ctx->Depth.Func==GL_LESS
                  && ctx->Depth.Mask==GL_TRUE)
                 || ctx->RasterMask==0)
             && ctx->Polygon.StippleFlag==GL_FALSE
             && ctx->Visual->EightBitColor) {
            if (ctx->RasterMask==DEPTH_BIT) {
               ctx->Driver.TriangleFunc = simple_z_textured_triangle;
            }
            else {
               ctx->Driver.TriangleFunc = simple_textured_triangle;
            }
         }
         else {
            GLboolean needLambda = GL_TRUE;
            /* if mag filter == min filter we're not mipmapping */
            if (ctx->Texture.Enabled & TEXTURE_2D) {
               if (ctx->Texture.Current2D->MinFilter==
                   ctx->Texture.Current2D->MagFilter) {
                  needLambda = GL_FALSE;
               }
            }
            else if (ctx->Texture.Enabled & TEXTURE_1D) {
               if (ctx->Texture.Current1D->MinFilter==
                   ctx->Texture.Current1D->MagFilter) {
                  needLambda = GL_FALSE;
               }
            }
            if (needLambda)
               ctx->Driver.TriangleFunc = lambda_textured_triangle;
            else
               ctx->Driver.TriangleFunc = general_textured_triangle;
         }
      }
      else {
	 if (ctx->Light.ShadeModel==GL_SMOOTH) {
	    /* smooth shaded, no texturing, stippled or some raster ops */
            if (rgbmode)
               ctx->Driver.TriangleFunc = smooth_rgba_triangle;
            else
               ctx->Driver.TriangleFunc = smooth_ci_triangle;
	 }
	 else {
	    /* flat shaded, no texturing, stippled or some raster ops */
            if (rgbmode)
               ctx->Driver.TriangleFunc = flat_rgba_triangle;
            else
               ctx->Driver.TriangleFunc = flat_ci_triangle;
	 }
      }
   }
   else if (ctx->RenderMode==GL_FEEDBACK) {
      ctx->Driver.TriangleFunc = feedback_triangle;
   }
   else {
      /* GL_SELECT mode */
      ctx->Driver.TriangleFunc = select_triangle;
   }
}