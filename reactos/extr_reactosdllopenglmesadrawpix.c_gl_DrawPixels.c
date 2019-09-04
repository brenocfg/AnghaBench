#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ (* DrawPixels ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ;} ;
struct TYPE_12__ {scalar_t__* RasterPos; } ;
struct TYPE_14__ {scalar_t__ RenderMode; scalar_t__ RasterMask; scalar_t__ CallDepth; scalar_t__ CompileFlag; scalar_t__ ExecuteFlag; scalar_t__ FastDrawPixels; TYPE_2__ Driver; TYPE_1__ Current; scalar_t__ NewState; } ;
typedef  int /*<<< orphan*/  const GLvoid ;
typedef  scalar_t__ GLsizei ;
typedef  int /*<<< orphan*/  GLint ;
typedef  scalar_t__ GLenum ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_INVALID_VALUE ; 
 int /*<<< orphan*/  GL_OUT_OF_MEMORY ; 
 scalar_t__ GL_RENDER ; 
 scalar_t__ GL_RGB ; 
 scalar_t__ GL_UNSIGNED_BYTE ; 
 int /*<<< orphan*/  drawpixels (TYPE_3__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  gl_error (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gl_save_DrawPixels (TYPE_3__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* gl_unpack_pixels (TYPE_3__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  gl_update_state (TYPE_3__*) ; 
 scalar_t__ quickdraw_rgb (TYPE_3__*,scalar_t__,scalar_t__,int /*<<< orphan*/  const*) ; 
 scalar_t__ stub1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

void gl_DrawPixels( GLcontext* ctx, GLsizei width, GLsizei height,
                    GLenum format, GLenum type, const GLvoid *pixels )
{
   GLvoid *image;

   if (width<0 || height<0) {
      gl_error( ctx, GL_INVALID_VALUE, "glDrawPixels" );
      return;
   }

   if (ctx->NewState) {
      gl_update_state(ctx);
   }

   /* Let the device driver take a crack at glDrawPixels */
   if (!ctx->CompileFlag && ctx->Driver.DrawPixels) {
      GLint x = (GLint) (ctx->Current.RasterPos[0] + 0.5F);
      GLint y = (GLint) (ctx->Current.RasterPos[1] + 0.5F);
      if ((*ctx->Driver.DrawPixels)( ctx, x, y, width, height,
                                      format, type, GL_FALSE, pixels )) {
         /* Device driver did the job */
         return;
      }
   }

   if (format==GL_RGB && type==GL_UNSIGNED_BYTE && ctx->FastDrawPixels
       && !ctx->CompileFlag && ctx->RenderMode==GL_RENDER
       && ctx->RasterMask==0 && ctx->CallDepth==0) {
      /* optimized path */
      if (quickdraw_rgb( ctx, width, height, pixels )) {
         /* success */
         return;
      }
   }

   /* take the general path */

   /* THIS IS A REAL HACK - FIX IN MESA 2.5
    * If we're inside glCallList then we don't have to unpack the pixels again.
    */
   if (ctx->CallDepth == 0) {
      image = gl_unpack_pixels( ctx, width, height, format, type, pixels );
      if (!image) {
         gl_error( ctx, GL_OUT_OF_MEMORY, "glDrawPixels" );
         return;
      }
   }
   else {
      image = (GLvoid *) pixels;
   }

   if (ctx->CompileFlag) {
      gl_save_DrawPixels( ctx, width, height, format, type, image );
   }
   if (ctx->ExecuteFlag) {
      drawpixels( ctx, width, height, format, type, image );
      if (!ctx->CompileFlag) {
         /* may discard unpacked image now */
         if (image!=pixels)
            free( image );
      }
   }
}