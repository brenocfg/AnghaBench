#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {float* ByteColor; float* TexCoord; int /*<<< orphan*/ * RasterPos; scalar_t__ RasterPosValid; int /*<<< orphan*/  Index; } ;
struct TYPE_16__ {scalar_t__ RenderMode; TYPE_2__ Current; TYPE_1__* Visual; } ;
struct TYPE_14__ {float InvRedScale; float InvGreenScale; float InvBlueScale; float InvAlphaScale; } ;
typedef  int /*<<< orphan*/  GLvoid ;
typedef  int /*<<< orphan*/  GLsizei ;
typedef  scalar_t__ GLint ;
typedef  float GLfloat ;
typedef  int GLenum ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  FEEDBACK_TOKEN (TYPE_3__*,float) ; 
#define  GL_ALPHA 140 
#define  GL_BGRA_EXT 139 
#define  GL_BGR_EXT 138 
#define  GL_BLUE 137 
#define  GL_COLOR_INDEX 136 
#define  GL_DEPTH_COMPONENT 135 
 scalar_t__ GL_DRAW_PIXEL_TOKEN ; 
 scalar_t__ GL_FEEDBACK ; 
#define  GL_GREEN 134 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
#define  GL_LUMINANCE 133 
#define  GL_LUMINANCE_ALPHA 132 
#define  GL_RED 131 
 scalar_t__ GL_RENDER ; 
#define  GL_RGB 130 
#define  GL_RGBA 129 
 scalar_t__ GL_SELECT ; 
#define  GL_STENCIL_INDEX 128 
 scalar_t__ INSIDE_BEGIN_END (TYPE_3__*) ; 
 int /*<<< orphan*/  draw_color_pixels (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  draw_depth_pixels (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  draw_index_pixels (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  draw_stencil_pixels (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  gl_error (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gl_feedback_vertex (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  gl_update_hitflag (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void drawpixels( GLcontext* ctx, GLsizei width, GLsizei height,
                        GLenum format, GLenum type, const GLvoid *pixels )
{
   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glDrawPixels" );
      return;
   }

   if (ctx->RenderMode==GL_RENDER) {
      if (!ctx->Current.RasterPosValid) {
	 return;
      }
      switch (format) {
	 case GL_COLOR_INDEX:
            draw_index_pixels( ctx, width, height, type, pixels );
	    break;
	 case GL_STENCIL_INDEX:
	    draw_stencil_pixels( ctx, width, height, type, pixels );
	    break;
	 case GL_DEPTH_COMPONENT:
	    draw_depth_pixels( ctx, width, height, type, pixels );
	    break;
	 case GL_RED:
	 case GL_GREEN:
	 case GL_BLUE:
	 case GL_ALPHA:
	 case GL_RGB:
	 case GL_BGR_EXT:
	 case GL_LUMINANCE:
	 case GL_LUMINANCE_ALPHA:
	 case GL_RGBA:
	 case GL_BGRA_EXT:
            draw_color_pixels( ctx, width, height, format, type, pixels );
	    break;
	 default:
	    gl_error( ctx, GL_INVALID_ENUM, "glDrawPixels" );
      }
   }
   else if (ctx->RenderMode==GL_FEEDBACK) {
      if (ctx->Current.RasterPosValid) {
         GLfloat color[4], texcoord[4], invq;
         color[0] = ctx->Current.ByteColor[0] * ctx->Visual->InvRedScale;
         color[1] = ctx->Current.ByteColor[1] * ctx->Visual->InvGreenScale;
         color[2] = ctx->Current.ByteColor[2] * ctx->Visual->InvBlueScale;
         color[3] = ctx->Current.ByteColor[3] * ctx->Visual->InvAlphaScale;
         invq = 1.0F / ctx->Current.TexCoord[3];
         texcoord[0] = ctx->Current.TexCoord[0] * invq;
         texcoord[1] = ctx->Current.TexCoord[1] * invq;
         texcoord[2] = ctx->Current.TexCoord[2] * invq;
         texcoord[3] = ctx->Current.TexCoord[3];
         FEEDBACK_TOKEN( ctx, (GLfloat) (GLint) GL_DRAW_PIXEL_TOKEN );
         gl_feedback_vertex( ctx, ctx->Current.RasterPos[0],
                             ctx->Current.RasterPos[1],
                             ctx->Current.RasterPos[2],
                             ctx->Current.RasterPos[3],
                             color, ctx->Current.Index, texcoord );
      }
   }
   else if (ctx->RenderMode==GL_SELECT) {
      if (ctx->Current.RasterPosValid) {
         gl_update_hitflag( ctx, ctx->Current.RasterPos[2] );
      }
   }
}