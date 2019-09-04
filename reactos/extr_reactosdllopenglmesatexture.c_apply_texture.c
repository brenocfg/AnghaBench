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
typedef  scalar_t__ t ;
typedef  scalar_t__ s ;
typedef  int /*<<< orphan*/  red ;
typedef  int /*<<< orphan*/  green ;
typedef  int /*<<< orphan*/  blue ;
typedef  int /*<<< orphan*/  alpha ;
struct TYPE_6__ {float* EnvColor; } ;
struct TYPE_8__ {TYPE_2__* Visual; TYPE_1__ Texture; } ;
struct TYPE_7__ {double InvRedScale; double InvGreenScale; double InvBlueScale; double InvAlphaScale; float RedScale; float GreenScale; float BlueScale; float AlphaScale; int /*<<< orphan*/  EightBitColor; } ;
typedef  int /*<<< orphan*/  Rt ;
typedef  scalar_t__ Rc ;
typedef  scalar_t__ Lt ;
typedef  scalar_t__ It ;
typedef  int /*<<< orphan*/  Gt ;
typedef  scalar_t__ Gc ;
typedef  size_t GLuint ;
typedef  scalar_t__ GLubyte ;
typedef  scalar_t__ GLint ;
typedef  scalar_t__ GLfloat ;
typedef  int GLenum ;
typedef  TYPE_3__ GLcontext ;
typedef  int /*<<< orphan*/  Bt ;
typedef  scalar_t__ Bc ;
typedef  int /*<<< orphan*/  At ;
typedef  scalar_t__ Ac ;

/* Variables and functions */
#define  GL_ALPHA 137 
#define  GL_BLEND 136 
 scalar_t__ GL_COLOR_INDEX ; 
#define  GL_DECAL 135 
#define  GL_INTENSITY 134 
#define  GL_LUMINANCE 133 
#define  GL_LUMINANCE_ALPHA 132 
#define  GL_MODULATE 131 
#define  GL_REPLACE 130 
#define  GL_RGB 129 
#define  GL_RGBA 128 
 int /*<<< orphan*/  gl_problem (TYPE_3__*,char*) ; 

__attribute__((used)) static void apply_texture( GLcontext *ctx,
         GLuint n, GLint format, GLenum env_mode,
	 GLubyte red[], GLubyte green[], GLubyte blue[], GLubyte alpha[],
	 GLubyte Rt[], GLubyte Gt[], GLubyte Bt[], GLubyte At[] )
{
   GLuint i;
   GLint Rc, Gc, Bc, Ac;

   if (!ctx->Visual->EightBitColor) {
      /* This is a hack!  Rescale input colors from [0,scale] to [0,255]. */
      GLfloat rscale = 255.0 * ctx->Visual->InvRedScale;
      GLfloat gscale = 255.0 * ctx->Visual->InvGreenScale;
      GLfloat bscale = 255.0 * ctx->Visual->InvBlueScale;
      GLfloat ascale = 255.0 * ctx->Visual->InvAlphaScale;
      for (i=0;i<n;i++) {
	 red[i]   = (GLint) (red[i]   * rscale);
	 green[i] = (GLint) (green[i] * gscale);
	 blue[i]  = (GLint) (blue[i]  * bscale);
	 alpha[i] = (GLint) (alpha[i] * ascale);
      }
   }

/*
 * Use (A*(B+1)) >> 8 as a fast approximation of (A*B)/255 for A
 * and B in [0,255]
 */
#define PROD(A,B)   (((GLint)(A) * ((GLint)(B)+1)) >> 8)

   if (format==GL_COLOR_INDEX) {
      format = GL_RGBA;  /* XXXX a hack! */
   }

   switch (env_mode) {
      case GL_REPLACE:
	 switch (format) {
	    case GL_ALPHA:
	       for (i=0;i<n;i++) {
		  /* Cv = Cf */
                  /* Av = At */
                  alpha[i] = At[i];
	       }
	       break;
	    case GL_LUMINANCE:
	       for (i=0;i<n;i++) {
		  /* Cv = Lt */
                  GLint Lt = Rt[i];
                  red[i] = green[i] = blue[i] = Lt;
                  /* Av = Af */
	       }
	       break;
	    case GL_LUMINANCE_ALPHA:
	       for (i=0;i<n;i++) {
                  GLint Lt = Rt[i];
		  /* Cv = Lt */
		  red[i] = green[i] = blue[i] = Lt;
		  /* Av = At */
		  alpha[i] = At[i];
	       }
	       break;
	    case GL_INTENSITY:
	       for (i=0;i<n;i++) {
		  /* Cv = It */
                  GLint It = Rt[i];
                  red[i] = green[i] = blue[i] = It;
                  /* Av = It */
                  alpha[i] = It;
	       }
	       break;
	    case GL_RGB:
	       for (i=0;i<n;i++) {
		  /* Cv = Ct */
		  red[i]   = Rt[i];
		  green[i] = Gt[i];
		  blue[i]  = Bt[i];
		  /* Av = Af */
	       }
	       break;
	    case GL_RGBA:
	       for (i=0;i<n;i++) {
		  /* Cv = Ct */
		  red[i]   = Rt[i];
		  green[i] = Gt[i];
		  blue[i]  = Bt[i];
		  /* Av = At */
		  alpha[i] = At[i];
	       }
	       break;
            default:
               gl_problem(ctx, "Bad format in apply_texture");
               return;
	 }
	 break;

      case GL_MODULATE:
         switch (format) {
	    case GL_ALPHA:
	       for (i=0;i<n;i++) {
		  /* Cv = Cf */
		  /* Av = AfAt */
		  alpha[i] = PROD( alpha[i], At[i] );
	       }
	       break;
	    case GL_LUMINANCE:
	       for (i=0;i<n;i++) {
		  /* Cv = LtCf */
                  GLint Lt = Rt[i];
		  red[i]   = PROD( red[i],   Lt );
		  green[i] = PROD( green[i], Lt );
		  blue[i]  = PROD( blue[i],  Lt );
		  /* Av = Af */
	       }
	       break;
	    case GL_LUMINANCE_ALPHA:
	       for (i=0;i<n;i++) {
		  /* Cv = CfLt */
                  GLint Lt = Rt[i];
		  red[i]   = PROD( red[i],   Lt );
		  green[i] = PROD( green[i], Lt );
		  blue[i]  = PROD( blue[i],  Lt );
		  /* Av = AfAt */
		  alpha[i] = PROD( alpha[i], At[i] );
	       }
	       break;
	    case GL_INTENSITY:
	       for (i=0;i<n;i++) {
		  /* Cv = CfIt */
                  GLint It = Rt[i];
		  red[i]   = PROD( red[i],   It );
		  green[i] = PROD( green[i], It );
		  blue[i]  = PROD( blue[i],  It );
		  /* Av = AfIt */
		  alpha[i] = PROD( alpha[i], It );
	       }
	       break;
	    case GL_RGB:
	       for (i=0;i<n;i++) {
		  /* Cv = CfCt */
		  red[i]   = PROD( red[i],   Rt[i] );
		  green[i] = PROD( green[i], Gt[i] );
		  blue[i]  = PROD( blue[i],  Bt[i] );
		  /* Av = Af */
	       }
	       break;
	    case GL_RGBA:
	       for (i=0;i<n;i++) {
		  /* Cv = CfCt */
		  red[i]   = PROD( red[i],   Rt[i] );
		  green[i] = PROD( green[i], Gt[i] );
		  blue[i]  = PROD( blue[i],  Bt[i] );
		  /* Av = AfAt */
		  alpha[i] = PROD( alpha[i], At[i] );
	       }
	       break;
            default:
               gl_problem(ctx, "Bad format (2) in apply_texture");
               return;
	 }
	 break;

      case GL_DECAL:
         switch (format) {
            case GL_ALPHA:
            case GL_LUMINANCE:
            case GL_LUMINANCE_ALPHA:
            case GL_INTENSITY:
               /* undefined */
               break;
	    case GL_RGB:
	       for (i=0;i<n;i++) {
		  /* Cv = Ct */
		  red[i]   = Rt[i];
		  green[i] = Gt[i];
		  blue[i]  = Bt[i];
		  /* Av = Af */
	       }
	       break;
	    case GL_RGBA:
	       for (i=0;i<n;i++) {
		  /* Cv = Cf(1-At) + CtAt */
		  GLint t = At[i], s = 255 - t;
		  red[i]   = PROD(red[i],  s) + PROD(Rt[i],t);
		  green[i] = PROD(green[i],s) + PROD(Gt[i],t);
		  blue[i]  = PROD(blue[i], s) + PROD(Bt[i],t);
		  /* Av = Af */
	       }
	       break;
            default:
               gl_problem(ctx, "Bad format (3) in apply_texture");
               return;
	 }
	 break;

      case GL_BLEND:
         Rc = (GLint) (ctx->Texture.EnvColor[0] * 255.0F);
         Gc = (GLint) (ctx->Texture.EnvColor[1] * 255.0F);
         Bc = (GLint) (ctx->Texture.EnvColor[2] * 255.0F);
         Ac = (GLint) (ctx->Texture.EnvColor[3] * 255.0F);
	 switch (format) {
	    case GL_ALPHA:
	       for (i=0;i<n;i++) {
		  /* Cv = Cf */
		  /* Av = AfAt */
                  alpha[i] = PROD(alpha[i], At[i]);
	       }
	       break;
            case GL_LUMINANCE:
	       for (i=0;i<n;i++) {
		  /* Cv = Cf(1-Lt) + CcLt */
		  GLint Lt = Rt[i], s = 255 - Lt;
		  red[i]   = PROD(red[i],  s) + PROD(Rc,  Lt);
		  green[i] = PROD(green[i],s) + PROD(Gc,Lt);
		  blue[i]  = PROD(blue[i], s) + PROD(Bc, Lt);
		  /* Av = Af */
	       }
	       break;
	    case GL_LUMINANCE_ALPHA:
	       for (i=0;i<n;i++) {
		  /* Cv = Cf(1-Lt) + CcLt */
		  GLint Lt = Rt[i], s = 255 - Lt;
		  red[i]   = PROD(red[i],  s) + PROD(Rc,  Lt);
		  green[i] = PROD(green[i],s) + PROD(Gc,Lt);
		  blue[i]  = PROD(blue[i], s) + PROD(Bc, Lt);
		  /* Av = AfAt */
		  alpha[i] = PROD(alpha[i],At[i]);
	       }
	       break;
            case GL_INTENSITY:
	       for (i=0;i<n;i++) {
		  /* Cv = Cf(1-It) + CcLt */
		  GLint It = Rt[i], s = 255 - It;
		  red[i]   = PROD(red[i],  s) + PROD(Rc,It);
		  green[i] = PROD(green[i],s) + PROD(Gc,It);
		  blue[i]  = PROD(blue[i], s) + PROD(Bc,It);
                  /* Av = Af(1-It) + Ac*It */
                  alpha[i] = PROD(alpha[i],s) + PROD(Ac,It);
               }
               break;
	    case GL_RGB:
	       for (i=0;i<n;i++) {
		  /* Cv = Cf(1-Ct) + CcCt */
		  red[i]   = PROD(red[i],  (255-Rt[i])) + PROD(Rc,Rt[i]);
		  green[i] = PROD(green[i],(255-Gt[i])) + PROD(Gc,Gt[i]);
		  blue[i]  = PROD(blue[i], (255-Bt[i])) + PROD(Bc,Bt[i]);
		  /* Av = Af */
	       }
	       break;
	    case GL_RGBA:
	       for (i=0;i<n;i++) {
		  /* Cv = Cf(1-Ct) + CcCt */
		  red[i]   = PROD(red[i],  (255-Rt[i])) + PROD(Rc,Rt[i]);
		  green[i] = PROD(green[i],(255-Gt[i])) + PROD(Gc,Gt[i]);
		  blue[i]  = PROD(blue[i], (255-Bt[i])) + PROD(Bc,Bt[i]);
		  /* Av = AfAt */
		  alpha[i] = PROD(alpha[i],At[i]);
	       }
	       break;
	 }
	 break;

      default:
         gl_problem(ctx, "Bad env mode in apply_texture");
         return;
   }
#undef PROD

   if (!ctx->Visual->EightBitColor) {
      /* This is a hack!  Rescale input colors from [0,255] to [0,scale]. */
      GLfloat rscale = ctx->Visual->RedScale   * (1.0F/ 255.0F);
      GLfloat gscale = ctx->Visual->GreenScale * (1.0F/ 255.0F);
      GLfloat bscale = ctx->Visual->BlueScale  * (1.0F/ 255.0F);
      GLfloat ascale = ctx->Visual->AlphaScale * (1.0F/ 255.0F);
      for (i=0;i<n;i++) {
	 red[i]   = (GLint) (red[i]   * rscale);
	 green[i] = (GLint) (green[i] * gscale);
	 blue[i]  = (GLint) (blue[i]  * bscale);
	 alpha[i] = (GLint) (alpha[i] * ascale);
      }
   }
}