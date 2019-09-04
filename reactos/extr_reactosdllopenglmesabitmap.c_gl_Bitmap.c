#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct gl_image {int dummy; } ;
struct TYPE_14__ {scalar_t__ RasterPosValid; float* ByteColor; float* TexCoord; float* RasterPos; int /*<<< orphan*/  Index; } ;
struct TYPE_12__ {scalar_t__ (* Bitmap ) (TYPE_4__*,scalar_t__,scalar_t__,float,float,float,float,struct gl_image const*) ;} ;
struct TYPE_15__ {scalar_t__ RenderMode; TYPE_3__ Current; TYPE_2__* Visual; TYPE_1__ Driver; } ;
struct TYPE_13__ {float InvRedScale; float InvGreenScale; float InvBlueScale; float InvAlphaScale; } ;
typedef  scalar_t__ GLsizei ;
typedef  scalar_t__ GLint ;
typedef  float GLfloat ;
typedef  TYPE_4__ GLcontext ;
typedef  scalar_t__ GLboolean ;

/* Variables and functions */
 int /*<<< orphan*/  FEEDBACK_TOKEN (TYPE_4__*,float) ; 
 scalar_t__ GL_BITMAP_TOKEN ; 
 scalar_t__ GL_FALSE ; 
 scalar_t__ GL_FEEDBACK ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
 int /*<<< orphan*/  GL_INVALID_VALUE ; 
 scalar_t__ GL_RENDER ; 
 scalar_t__ GL_SELECT ; 
 scalar_t__ INSIDE_BEGIN_END (TYPE_4__*) ; 
 int /*<<< orphan*/  gl_error (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gl_feedback_vertex (TYPE_4__*,float,float,float,float,float*,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  gl_render_bitmap (TYPE_4__*,scalar_t__,scalar_t__,float,float,float,float,struct gl_image const*) ; 
 scalar_t__ stub1 (TYPE_4__*,scalar_t__,scalar_t__,float,float,float,float,struct gl_image const*) ; 

void gl_Bitmap( GLcontext* ctx,
                GLsizei width, GLsizei height,
	        GLfloat xorig, GLfloat yorig,
	        GLfloat xmove, GLfloat ymove,
                const struct gl_image *bitmap )
{
   if (width<0 || height<0) {
      gl_error( ctx, GL_INVALID_VALUE, "glBitmap" );
      return;
   }
   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glBitmap" );
      return;
   }
   if (ctx->Current.RasterPosValid==GL_FALSE) {
      /* do nothing */
      return;
   }

   if (ctx->RenderMode==GL_RENDER) {
      GLboolean completed = GL_FALSE;
      if (ctx->Driver.Bitmap) {
         /* let device driver try to render the bitmap */
         completed = (*ctx->Driver.Bitmap)( ctx, width, height, xorig, yorig,
                                            xmove, ymove, bitmap );
      }
      if (!completed) {
         /* use generic function */
         gl_render_bitmap( ctx, width, height, xorig, yorig,
                           xmove, ymove, bitmap );
      }
   }
   else if (ctx->RenderMode==GL_FEEDBACK) {
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
      FEEDBACK_TOKEN( ctx, (GLfloat) (GLint) GL_BITMAP_TOKEN );
      /* TODO: Verify XYZW values are correct: */
      gl_feedback_vertex( ctx, ctx->Current.RasterPos[0] - xorig,
			  ctx->Current.RasterPos[1] - yorig,
			  ctx->Current.RasterPos[2],
			  ctx->Current.RasterPos[3],
			  color, ctx->Current.Index, texcoord );
   }
   else if (ctx->RenderMode==GL_SELECT) {
      /* Bitmaps don't generate selection hits.  See appendix B of 1.1 spec. */
   }

   /* update raster position */
   ctx->Current.RasterPos[0] += xmove;
   ctx->Current.RasterPos[1] += ymove;
}