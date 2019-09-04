#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* DepthBias; void* DepthScale; void* AlphaBias; void* AlphaScale; void* BlueBias; void* BlueScale; void* GreenBias; void* GreenScale; void* RedBias; void* RedScale; void* IndexOffset; void* IndexShift; void* MapStencilFlag; void* MapColorFlag; } ;
struct TYPE_8__ {TYPE_1__ Pixel; } ;
typedef  void* GLint ;
typedef  void* GLfloat ;
typedef  int GLenum ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
#define  GL_ALPHA_BIAS 141 
#define  GL_ALPHA_SCALE 140 
#define  GL_BLUE_BIAS 139 
#define  GL_BLUE_SCALE 138 
#define  GL_DEPTH_BIAS 137 
#define  GL_DEPTH_SCALE 136 
 void* GL_FALSE ; 
#define  GL_GREEN_BIAS 135 
#define  GL_GREEN_SCALE 134 
#define  GL_INDEX_OFFSET 133 
#define  GL_INDEX_SHIFT 132 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
#define  GL_MAP_COLOR 131 
#define  GL_MAP_STENCIL 130 
#define  GL_RED_BIAS 129 
#define  GL_RED_SCALE 128 
 void* GL_TRUE ; 
 scalar_t__ INSIDE_BEGIN_END (TYPE_2__*) ; 
 int /*<<< orphan*/  gl_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  update_drawpixels_state (TYPE_2__*) ; 

void gl_PixelTransferf( GLcontext *ctx, GLenum pname, GLfloat param )
{
   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glPixelTransfer" );
      return;
   }

   switch (pname) {
      case GL_MAP_COLOR:
         ctx->Pixel.MapColorFlag = param ? GL_TRUE : GL_FALSE;
	 break;
      case GL_MAP_STENCIL:
         ctx->Pixel.MapStencilFlag = param ? GL_TRUE : GL_FALSE;
	 break;
      case GL_INDEX_SHIFT:
         ctx->Pixel.IndexShift = (GLint) param;
	 break;
      case GL_INDEX_OFFSET:
         ctx->Pixel.IndexOffset = (GLint) param;
	 break;
      case GL_RED_SCALE:
         ctx->Pixel.RedScale = param;
	 break;
      case GL_RED_BIAS:
         ctx->Pixel.RedBias = param;
	 break;
      case GL_GREEN_SCALE:
         ctx->Pixel.GreenScale = param;
	 break;
      case GL_GREEN_BIAS:
         ctx->Pixel.GreenBias = param;
	 break;
      case GL_BLUE_SCALE:
         ctx->Pixel.BlueScale = param;
	 break;
      case GL_BLUE_BIAS:
         ctx->Pixel.BlueBias = param;
	 break;
      case GL_ALPHA_SCALE:
         ctx->Pixel.AlphaScale = param;
	 break;
      case GL_ALPHA_BIAS:
         ctx->Pixel.AlphaBias = param;
	 break;
      case GL_DEPTH_SCALE:
         ctx->Pixel.DepthScale = param;
	 break;
      case GL_DEPTH_BIAS:
         ctx->Pixel.DepthBias = param;
	 break;
      default:
         gl_error( ctx, GL_INVALID_ENUM, "glPixelTransfer(pname)" );
         return;
   }
   update_drawpixels_state( ctx );
}