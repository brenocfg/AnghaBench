#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_8__ ;
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;

/* Type definitions */
struct TYPE_36__ {size_t (* DepthTestSpan ) (TYPE_8__*,size_t,scalar_t__,scalar_t__,int /*<<< orphan*/ *,scalar_t__*) ;int /*<<< orphan*/  (* SetBuffer ) (TYPE_8__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* WriteMonocolorSpan ) (TYPE_8__*,size_t,scalar_t__,scalar_t__,scalar_t__*) ;int /*<<< orphan*/  (* WriteColorSpan ) (TYPE_8__*,size_t,scalar_t__,scalar_t__,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ;} ;
struct TYPE_35__ {scalar_t__ SWmasking; scalar_t__ BlendEnabled; scalar_t__ SWLogicOpEnabled; scalar_t__ AlphaEnabled; } ;
struct TYPE_34__ {scalar_t__ Test; } ;
struct TYPE_33__ {scalar_t__ Enabled; } ;
struct TYPE_32__ {scalar_t__ StippleFlag; } ;
struct TYPE_31__ {scalar_t__ Enabled; } ;
struct TYPE_37__ {int RasterMask; TYPE_1__* Buffer; TYPE_7__ Driver; TYPE_6__ Color; TYPE_5__ Depth; TYPE_4__ Stencil; TYPE_3__ Polygon; TYPE_2__ Scissor; } ;
struct TYPE_30__ {int /*<<< orphan*/  FrontAlpha; int /*<<< orphan*/  Alpha; int /*<<< orphan*/  BackAlpha; } ;
typedef  size_t GLuint ;
typedef  scalar_t__ GLubyte ;
typedef  scalar_t__ GLint ;
typedef  scalar_t__ GLenum ;
typedef  int /*<<< orphan*/  GLdepth ;
typedef  TYPE_8__ GLcontext ;
typedef  scalar_t__ GLboolean ;

/* Variables and functions */
 int ALPHABUF_BIT ; 
 int FRONT_AND_BACK_BIT ; 
 int /*<<< orphan*/  GL_BACK ; 
 scalar_t__ GL_BITMAP ; 
 scalar_t__ GL_FALSE ; 
 int /*<<< orphan*/  GL_FRONT ; 
 scalar_t__ GL_POLYGON ; 
 scalar_t__ GL_TRUE ; 
 int MAX_WIDTH ; 
 int /*<<< orphan*/  MEMSET (scalar_t__*,int,size_t) ; 
 int NO_DRAW_BIT ; 
 int WINCLIP_BIT ; 
 scalar_t__ clip_span (TYPE_8__*,size_t,scalar_t__,scalar_t__,scalar_t__*) ; 
 scalar_t__ gl_alpha_test (TYPE_8__*,size_t,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  gl_blend_span (TYPE_8__*,size_t,scalar_t__,scalar_t__,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  gl_depth_stencil_span (TYPE_8__*,size_t,scalar_t__,scalar_t__,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  gl_logicop_rgba_span (TYPE_8__*,size_t,scalar_t__,scalar_t__,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  gl_mask_color_span (TYPE_8__*,size_t,scalar_t__,scalar_t__,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ gl_scissor_span (TYPE_8__*,size_t,scalar_t__,scalar_t__,scalar_t__*) ; 
 scalar_t__ gl_stencil_span (TYPE_8__*,size_t,scalar_t__,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  gl_write_alpha_span (TYPE_8__*,size_t,scalar_t__,scalar_t__,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  gl_write_mono_alpha_span (TYPE_8__*,size_t,scalar_t__,scalar_t__,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  stipple_polygon_span (TYPE_8__*,size_t,scalar_t__,scalar_t__,scalar_t__*) ; 
 size_t stub1 (TYPE_8__*,size_t,scalar_t__,scalar_t__,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_8__*,size_t,scalar_t__,scalar_t__,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_8__*,size_t,scalar_t__,scalar_t__,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  stub5 (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (TYPE_8__*,size_t,scalar_t__,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  stub7 (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (TYPE_8__*,size_t,scalar_t__,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  stub9 (TYPE_8__*,int /*<<< orphan*/ ) ; 

void gl_write_monocolor_span( GLcontext *ctx,
                              GLuint n, GLint x, GLint y, GLdepth z[],
			      GLint r, GLint g, GLint b, GLint a,
                              GLenum primitive )
{
   GLuint i;
   GLubyte mask[MAX_WIDTH];
   GLboolean write_all = GL_TRUE;
   GLubyte red[MAX_WIDTH], green[MAX_WIDTH], blue[MAX_WIDTH], alpha[MAX_WIDTH];

   /* init mask to 1's (all pixels are to be written) */
   MEMSET(mask, 1, n);

   if ((ctx->RasterMask & WINCLIP_BIT) || primitive==GL_BITMAP) {
      if (clip_span( ctx,n,x,y,mask)==0) {
	 return;
      }
      write_all = GL_FALSE;
   }

   /* Do the scissor test */
   if (ctx->Scissor.Enabled) {
      if (gl_scissor_span( ctx, n, x, y, mask )==0) {
	 return;
      }
      write_all = GL_FALSE;
   }

   /* Polygon Stippling */
   if (ctx->Polygon.StippleFlag && primitive==GL_POLYGON) {
      stipple_polygon_span( ctx, n, x, y, mask );
      write_all = GL_FALSE;
   }

   /* Do the alpha test */
   if (ctx->Color.AlphaEnabled) {
      GLubyte alpha[MAX_WIDTH];
      for (i=0;i<n;i++) {
         alpha[i] = a;
      }
      if (gl_alpha_test( ctx, n, alpha, mask )==0) {
	 return;
      }
      write_all = GL_FALSE;
   }

   if (ctx->Stencil.Enabled) {
      /* first stencil test */
      if (gl_stencil_span( ctx, n, x, y, mask )==0) {
	 return;
      }
      /* depth buffering w/ stencil */
      gl_depth_stencil_span( ctx, n, x, y, z, mask );
      write_all = GL_FALSE;
   }
   else if (ctx->Depth.Test) {
      /* regular depth testing */
      GLuint m = (*ctx->Driver.DepthTestSpan)( ctx, n, x, y, z, mask );
      if (m==0) {
         return;
      }
      if (m<n) {
         write_all = GL_FALSE;
      }
   }

   if (ctx->RasterMask & NO_DRAW_BIT) {
      /* write no pixels */
      return;
   }

   if (ctx->Color.BlendEnabled || ctx->Color.SWLogicOpEnabled
       || ctx->Color.SWmasking) {
      /* assign same color to each pixel */
      for (i=0;i<n;i++) {
	 if (mask[i]) {
	    red[i]   = r;
	    green[i] = g;
	    blue[i]  = b;
	    alpha[i] = a;
	 }
      }

      if (ctx->Color.SWLogicOpEnabled) {
         gl_logicop_rgba_span( ctx, n, x, y, red, green, blue, alpha, mask );
      }
      else if (ctx->Color.BlendEnabled) {
         gl_blend_span( ctx, n, x, y, red, green, blue, alpha, mask );
      }

      /* Color component masking */
      if (ctx->Color.SWmasking) {
         gl_mask_color_span( ctx, n, x, y, red, green, blue, alpha );
      }

      /* write pixels */
      (*ctx->Driver.WriteColorSpan)( ctx, n, x, y, red, green, blue, alpha,
                                     write_all ? NULL : mask );
      if (ctx->RasterMask & ALPHABUF_BIT) {
         gl_write_alpha_span( ctx, n, x, y, alpha, write_all ? NULL : mask );
      }

      if (ctx->RasterMask & FRONT_AND_BACK_BIT) {
         /*** Also draw to back buffer ***/
         for (i=0;i<n;i++) {
            if (mask[i]) {
               red[i]   = r;
               green[i] = g;
               blue[i]  = b;
               alpha[i] = a;
            }
         }
         (*ctx->Driver.SetBuffer)( ctx, GL_BACK );
         if (ctx->Color.SWLogicOpEnabled) {
            gl_logicop_rgba_span( ctx, n, x, y, red, green, blue, alpha, mask);
         }
         else if (ctx->Color.BlendEnabled) {
            gl_blend_span( ctx, n, x, y, red, green, blue, alpha, mask );
         }
         if (ctx->Color.SWmasking) {
            gl_mask_color_span( ctx, n, x, y, red, green, blue, alpha );
         }
         (*ctx->Driver.WriteColorSpan)( ctx, n, x, y, red, green, blue, alpha,
                                        write_all ? NULL : mask );
         (*ctx->Driver.SetBuffer)( ctx, GL_FRONT );
         if (ctx->RasterMask & ALPHABUF_BIT) {
            ctx->Buffer->Alpha = ctx->Buffer->BackAlpha;
            gl_write_alpha_span( ctx, n, x, y, alpha,
                                 write_all ? NULL : mask );
            ctx->Buffer->Alpha = ctx->Buffer->FrontAlpha;
         }
      }
   }
   else {
      (*ctx->Driver.WriteMonocolorSpan)( ctx, n, x, y, mask );
      if (ctx->RasterMask & ALPHABUF_BIT) {
         gl_write_mono_alpha_span( ctx, n, x, y, a, write_all ? NULL : mask );
      }
      if (ctx->RasterMask & FRONT_AND_BACK_BIT) {
         /* Also draw to back buffer */
         (*ctx->Driver.SetBuffer)( ctx, GL_BACK );
         (*ctx->Driver.WriteMonocolorSpan)( ctx, n, x, y, mask );
         (*ctx->Driver.SetBuffer)( ctx, GL_FRONT );
         if (ctx->RasterMask & ALPHABUF_BIT) {
            ctx->Buffer->Alpha = ctx->Buffer->BackAlpha;
            gl_write_mono_alpha_span( ctx, n, x, y, a,
                                      write_all ? NULL : mask );
            ctx->Buffer->Alpha = ctx->Buffer->FrontAlpha;
         }
      }
   }
}