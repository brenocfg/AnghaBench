#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ RowLength; scalar_t__ SkipPixels; scalar_t__ SkipRows; scalar_t__ SwapBytes; scalar_t__ LsbFirst; } ;
struct TYPE_7__ {double RedBias; double RedScale; double GreenBias; double GreenScale; double BlueBias; double BlueScale; double AlphaBias; double AlphaScale; scalar_t__ MapColorFlag; double ZoomX; double ZoomY; } ;
struct TYPE_9__ {scalar_t__ FastDrawPixels; TYPE_3__ Unpack; TYPE_2__ Pixel; TYPE_1__* Visual; } ;
struct TYPE_6__ {scalar_t__ RGBAflag; scalar_t__ EightBitColor; } ;
typedef  TYPE_4__ GLcontext ;

/* Variables and functions */
 scalar_t__ GL_FALSE ; 
 scalar_t__ GL_TRUE ; 

__attribute__((used)) static void update_drawpixels_state( GLcontext *ctx )
{
   if (ctx->Visual->RGBAflag==GL_TRUE &&
       ctx->Visual->EightBitColor &&
       ctx->Pixel.RedBias==0.0   && ctx->Pixel.RedScale==1.0 &&
       ctx->Pixel.GreenBias==0.0 && ctx->Pixel.GreenScale==1.0 &&
       ctx->Pixel.BlueBias==0.0  && ctx->Pixel.BlueScale==1.0 &&
       ctx->Pixel.AlphaBias==0.0 && ctx->Pixel.AlphaScale==1.0 &&
       ctx->Pixel.MapColorFlag==GL_FALSE &&
       ctx->Pixel.ZoomX==1.0 && ctx->Pixel.ZoomY==1.0 &&
/*       ctx->Unpack.Alignment==4 &&*/
       ctx->Unpack.RowLength==0 &&
       ctx->Unpack.SkipPixels==0 &&
       ctx->Unpack.SkipRows==0 &&
       ctx->Unpack.SwapBytes==0 &&
       ctx->Unpack.LsbFirst==0) {
      ctx->FastDrawPixels = GL_TRUE;
   }
   else {
      ctx->FastDrawPixels = GL_FALSE;
   }
}