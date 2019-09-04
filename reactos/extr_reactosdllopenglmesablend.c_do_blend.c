#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int BlendSrc; int BlendDst; } ;
struct TYPE_8__ {TYPE_2__ Color; TYPE_1__* Visual; } ;
struct TYPE_6__ {float InvAlphaScale; int RedScale; int GreenScale; int BlueScale; int AlphaScale; scalar_t__ EightBitColor; } ;
typedef  size_t GLuint ;
typedef  int GLubyte ;
typedef  int GLint ;
typedef  int GLfloat ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 scalar_t__ CLAMP (int,float,int) ; 
#define  GL_DST_ALPHA 138 
#define  GL_DST_COLOR 137 
#define  GL_ONE 136 
#define  GL_ONE_MINUS_DST_ALPHA 135 
#define  GL_ONE_MINUS_DST_COLOR 134 
#define  GL_ONE_MINUS_SRC_ALPHA 133 
#define  GL_ONE_MINUS_SRC_COLOR 132 
#define  GL_SRC_ALPHA 131 
#define  GL_SRC_ALPHA_SATURATE 130 
#define  GL_SRC_COLOR 129 
#define  GL_ZERO 128 
 int MIN2 (int,int) ; 
 int /*<<< orphan*/  gl_problem (TYPE_3__*,char*) ; 

__attribute__((used)) static void do_blend( GLcontext* ctx, GLuint n, const GLubyte mask[],
                      GLubyte red[], GLubyte green[],
                      GLubyte blue[], GLubyte alpha[],
                      const GLubyte rdest[], const GLubyte gdest[],
                      const GLubyte bdest[], const GLubyte adest[] )
{
   GLuint i;

   if (ctx->Color.BlendSrc==GL_SRC_ALPHA
       && ctx->Color.BlendDst==GL_ONE_MINUS_SRC_ALPHA) {
      /* Alpha blending */
      GLfloat ascale = 256.0f * ctx->Visual->InvAlphaScale;
      GLint rmax = (GLint) ctx->Visual->RedScale;
      GLint gmax = (GLint) ctx->Visual->GreenScale;
      GLint bmax = (GLint) ctx->Visual->BlueScale;
      GLint amax = (GLint) ctx->Visual->AlphaScale;
      for (i=0;i<n;i++) {
	 if (mask[i]) {
	    GLint r, g, b, a;
            GLint t = (GLint) ( alpha[i] * ascale );  /* t in [0,256] */
            GLint s = 256 - t;
	    r = (red[i]   * t + rdest[i] * s) >> 8;
	    g = (green[i] * t + gdest[i] * s) >> 8;
	    b = (blue[i]  * t + bdest[i] * s) >> 8;
	    a = (alpha[i] * t + adest[i] * s) >> 8;

	    /* kai: I think the following clamping is not needed: */

	    red[i]   = MIN2( r, rmax );
	    green[i] = MIN2( g, gmax );
	    blue[i]  = MIN2( b, bmax );
	    alpha[i] = MIN2( a, amax );
	 }
      }
   }
   else {

      /* clipped sum */
      if (ctx->Color.BlendSrc==GL_ONE
	  && ctx->Color.BlendDst==GL_ONE) {
	 GLint rmax = (GLint) ctx->Visual->RedScale;
	 GLint gmax = (GLint) ctx->Visual->GreenScale;
	 GLint bmax = (GLint) ctx->Visual->BlueScale;
	 GLint amax = (GLint) ctx->Visual->AlphaScale;
	 for (i=0; i < n; i++) {
	    if (mask[i]) {
	       red[i]	= MIN2(rmax, red[i]   + rdest[i]);
	       green[i] = MIN2(gmax, green[i] + gdest[i]);
	       blue[i]	= MIN2(bmax, blue[i]  + bdest[i]);
	       alpha[i] = MIN2(amax, alpha[i] + adest[i]);
	    }
	 }
      }

      /* modulation */
      else if ((ctx->Color.BlendSrc==GL_ZERO &&
		    ctx->Color.BlendDst==GL_SRC_COLOR)
	       ||
	       (ctx->Color.BlendSrc==GL_DST_COLOR &&
		    ctx->Color.BlendDst==GL_ZERO)) {
	 if (ctx->Visual->EightBitColor) {
	    for (i=0; i < n; i++) {
	       if (mask[i]) {
		  red[i]   = (red[i]   * rdest[i]) / 255;
		  green[i] = (green[i] * gdest[i]) / 255;
		  blue[i]  = (blue[i]  * bdest[i]) / 255;
		  alpha[i] = (alpha[i] * adest[i]) / 255;
	       }
	    }
	 }
         else {
	    GLint rmax = (GLint) ctx->Visual->RedScale;
	    GLint gmax = (GLint) ctx->Visual->GreenScale;
	    GLint bmax = (GLint) ctx->Visual->BlueScale;
	    GLint amax = (GLint) ctx->Visual->AlphaScale;
	    for (i=0; i < n; i++) {
	       if (mask[i]) {
		  red[i]   = (red[i]   * rdest[i]) / rmax;
		  green[i] = (green[i] * gdest[i]) / gmax;
		  blue[i]  = (blue[i]  * bdest[i]) / bmax;
		  alpha[i] = (alpha[i] * adest[i]) / amax;
	       }
	    }
	 }
      }else{

	 /* General cases: */

	 if (ctx->Visual->EightBitColor) {
	    for (i=0;i<n;i++) {
	       if (mask[i]) {
		  GLint Rs, Gs, Bs, As;	 /* Source colors */
		  GLint Rd, Gd, Bd, Ad;	 /* Dest colors */
		  GLint Rss, Gss, Bss, Ass;  /* Source colors scaled */
		  GLint Rds, Gds, Bds, Ads;  /* Dest colors scaled */

		  /* Source Color */
		  Rs = red[i];
		  Gs = green[i];
		  Bs = blue[i];
		  As = alpha[i];

		  /* Frame buffer color */
		  Rd = rdest[i];
		  Gd = gdest[i];
		  Bd = bdest[i];
		  Ad = adest[i];

		  /* Source scaling */
		  switch (ctx->Color.BlendSrc) {
		     case GL_ZERO:
			Rss = Gss = Bss = Ass = 0;
			break;
		     case GL_ONE:
			Rss = Rs * 255;
			Gss = Gs * 255;
			Bss = Bs * 255;
			Ass = As * 255;
			break;
		     case GL_DST_COLOR:
			Rss = Rs * Rd;
			Gss = Gs * Gd;
			Bss = Bs * Bd;
			Ass = As * Ad;
			break;
		     case GL_ONE_MINUS_DST_COLOR:
			Rss = Rs * (255 - Rd);
			Gss = Gs * (255 - Gd);
			Bss = Bs * (255 - Bd);
			Ass = As * (255 - Ad);
			break;
		     case GL_SRC_ALPHA:
			Rss = Rs * As;
			Gss = Gs * As;
			Bss = Bs * As;
			Ass = As * As;
			break;
		     case GL_ONE_MINUS_SRC_ALPHA:
			Rss = Rs * (255 - As);
			Gss = Gs * (255 - As);
			Bss = Bs * (255 - As);
			Ass = As * (255 - As);
			break;
		     case GL_DST_ALPHA:
			Rss = Rs * Ad;
			Gss = Gs * Ad;
			Bss = Bs * Ad;
			Ass = As * Ad;
			break;
		     case GL_ONE_MINUS_DST_ALPHA:
			Rss = Rs * (255 - Ad);
			Gss = Gs * (255 - Ad);
			Bss = Bs * (255 - Ad);
			Ass = As * (255 - Ad);
			break;
		     case GL_SRC_ALPHA_SATURATE:
		     {
                GLint sA = MIN2(As, 255 - Ad);
                Rss = Rs * sA;
                Gss = Gs * sA;
                Bss = Bs * sA;
                Ass = As * 255;
                break;
		     }
		     default:
			/* this should never happen */
			gl_problem(ctx, "Bad blend source factor in do_blend");
		  }

		  /* Dest scaling */
		  switch (ctx->Color.BlendDst) {
		     case GL_ZERO:
			Rds = Gds = Bds = Ads = 0;
			break;
		     case GL_ONE:
			Rds = Rd * 255;
			Gds = Gd * 255;
			Bds = Bd * 255;
			Ads = Ad * 255;
			break;
		     case GL_SRC_COLOR:
			Rds = Rd * Rs;
			Gds = Gd * Gs;
			Bds = Bd * Bs;
			Ads = Ad * As;
			break;
		     case GL_ONE_MINUS_SRC_COLOR:
			Rds = Rs * (255 - Rs);
			Gds = Gs * (255 - Gs);
			Bds = Bs * (255 - Bs);
			Ads = As * (255 - As);
			break;
		     case GL_SRC_ALPHA:
			Rds = Rd * As;
			Gds = Gd * As;
			Bds = Bd * As;
			Ads = Ad * As;
			break;
		     case GL_ONE_MINUS_SRC_ALPHA:
			Rds = Rd * (255 - As);
			Gds = Gd * (255 - As);
			Bds = Bd * (255 - As);
			Ads = Ad * (255 - As);
			break;
		     case GL_DST_ALPHA:
			Rds = Rd * Ad;
			Gds = Gd * Ad;
			Bds = Bd * Ad;
			Ads = Ad * Ad;
			break;
		     case GL_ONE_MINUS_DST_ALPHA:
			Rds = Rd * (255 - Ad);
			Gds = Gd * (255 - Ad);
			Bds = Bd * (255 - Ad);
			Ads = Ad * (255 - Ad);
			break;
		     default:
			/* this should never happen */
			gl_problem(ctx, "Bad blend dest factor in do_blend");
		  }

		  /* compute blended color */
			red[i]	 = MIN2((Rss + Rds) / 255, 255);
			green[i] = MIN2((Gss + Gds) / 255, 255);
			blue[i]	 = MIN2((Bss + Bds) / 255, 255);
			alpha[i] = MIN2((Ass + Ads) / 255, 255);
	       }
	    }
	 }else{			/* !EightBitColor */
	    GLfloat rmax = ctx->Visual->RedScale;
	    GLfloat gmax = ctx->Visual->GreenScale;
	    GLfloat bmax = ctx->Visual->BlueScale;
	    GLfloat amax = ctx->Visual->AlphaScale;
	    GLfloat rscale = 1.0f / rmax;
	    GLfloat gscale = 1.0f / gmax;
	    GLfloat bscale = 1.0f / bmax;
	    GLfloat ascale = 1.0f / amax;

	    for (i=0;i<n;i++) {
	       if (mask[i]) {
		  GLint Rs, Gs, Bs, As;	 /* Source colors */
		  GLint Rd, Gd, Bd, Ad;	 /* Dest colors */
		  GLfloat sR, sG, sB, sA;  /* Source scaling */
		  GLfloat dR, dG, dB, dA;  /* Dest scaling */
		  GLfloat r, g, b, a;

		  /* Source Color */
		  Rs = red[i];
		  Gs = green[i];
		  Bs = blue[i];
		  As = alpha[i];

		  /* Frame buffer color */
		  Rd = rdest[i];
		  Gd = gdest[i];
		  Bd = bdest[i];
		  Ad = adest[i];

		  /* Source scaling */
		  switch (ctx->Color.BlendSrc) {
		     case GL_ZERO:
			sR = sG = sB = sA = 0.0F;
			break;
		     case GL_ONE:
			sR = sG = sB = sA = 1.0F;
			break;
		     case GL_DST_COLOR:
			sR = (GLfloat) Rd * rscale;
			sG = (GLfloat) Gd * gscale;
			sB = (GLfloat) Bd * bscale;
			sA = (GLfloat) Ad * ascale;
			break;
		     case GL_ONE_MINUS_DST_COLOR:
			sR = 1.0F - (GLfloat) Rd * rscale;
			sG = 1.0F - (GLfloat) Gd * gscale;
			sB = 1.0F - (GLfloat) Bd * bscale;
			sA = 1.0F - (GLfloat) Ad * ascale;
			break;
		     case GL_SRC_ALPHA:
			sR = sG = sB = sA = (GLfloat) As * ascale;
			break;
		     case GL_ONE_MINUS_SRC_ALPHA:
			sR = sG = sB = sA = (GLfloat) 1.0F - (GLfloat) As * ascale;
			break;
		     case GL_DST_ALPHA:
			sR = sG = sB = sA =(GLfloat) Ad * ascale;
			break;
		     case GL_ONE_MINUS_DST_ALPHA:
			sR = sG = sB = sA = 1.0F - (GLfloat) Ad * ascale;
			break;
		     case GL_SRC_ALPHA_SATURATE:
			if (As < 1.0F - (GLfloat) Ad * ascale) {
			   sR = sG = sB = (GLfloat) As * ascale;
			}
			else {
			   sR = sG = sB = 1.0F - (GLfloat) Ad * ascale;
			}
			sA = 1.0;
			break;
		     default:
			/* this should never happen */
			gl_problem(ctx, "Bad blend source factor in do_blend");
		  }

		  /* Dest scaling */
		  switch (ctx->Color.BlendDst) {
		     case GL_ZERO:
			dR = dG = dB = dA = 0.0F;
			break;
		     case GL_ONE:
			dR = dG = dB = dA = 1.0F;
			break;
		     case GL_SRC_COLOR:
			dR = (GLfloat) Rs * rscale;
			dG = (GLfloat) Gs * gscale;
			dB = (GLfloat) Bs * bscale;
			dA = (GLfloat) As * ascale;
			break;
		     case GL_ONE_MINUS_SRC_COLOR:
			dR = 1.0F - (GLfloat) Rs * rscale;
			dG = 1.0F - (GLfloat) Gs * gscale;
			dB = 1.0F - (GLfloat) Bs * bscale;
			dA = 1.0F - (GLfloat) As * ascale;
			break;
		     case GL_SRC_ALPHA:
			dR = dG = dB = dA = (GLfloat) As * ascale;
			break;
		     case GL_ONE_MINUS_SRC_ALPHA:
			dR = dG = dB = dA = (GLfloat) 1.0F - (GLfloat) As * ascale;
			break;
		     case GL_DST_ALPHA:
			dR = dG = dB = dA = (GLfloat) Ad * ascale;
			break;
		     case GL_ONE_MINUS_DST_ALPHA:
			dR = dG = dB = dA = 1.0F - (GLfloat) Ad * ascale;
			break;
		     default:
			/* this should never happen */
			gl_problem(ctx, "Bad blend dest factor in do_blend");
		  }

#ifdef DEBUG
		  assert( sR>= 0.0 && sR<=1.0 );
		  assert( sG>= 0.0 && sG<=1.0 );
		  assert( sB>= 0.0 && sB<=1.0 );
		  assert( sA>= 0.0 && sA<=1.0 );
		  assert( dR>= 0.0 && dR<=1.0 );
		  assert( dG>= 0.0 && dG<=1.0 );
		  assert( dB>= 0.0 && dB<=1.0 );
		  assert( dA>= 0.0 && dA<=1.0 );
#endif

		  /* compute blended color */
		  r = Rs * sR + Rd * dR;
		  g = Gs * sG + Gd * dG;
		  b = Bs * sB + Bd * dB;
		  a = As * sA + Ad * dA;
		  red[i]   = (GLint) CLAMP( r, 0.0F, rmax );
		  green[i] = (GLint) CLAMP( g, 0.0F, gmax );
		  blue[i]  = (GLint) CLAMP( b, 0.0F, bmax );
		  alpha[i] = (GLint) CLAMP( a, 0.0F, amax );
	       }
	    }
	 }
      }
   }

}