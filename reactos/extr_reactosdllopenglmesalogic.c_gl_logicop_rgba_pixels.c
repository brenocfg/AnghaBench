#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int LogicOp; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* ReadColorPixels ) (TYPE_4__*,size_t,int const*,int const*,int*,int*,int*,int*,int*) ;} ;
struct TYPE_12__ {int RasterMask; TYPE_1__* Visual; TYPE_3__ Color; TYPE_2__ Driver; } ;
struct TYPE_9__ {int /*<<< orphan*/  AlphaScale; int /*<<< orphan*/  BlueScale; int /*<<< orphan*/  GreenScale; int /*<<< orphan*/  RedScale; } ;
typedef  size_t GLuint ;
typedef  int GLubyte ;
typedef  int GLint ;
typedef  TYPE_4__ GLcontext ;

/* Variables and functions */
 int ALPHABUF_BIT ; 
#define  GL_AND 143 
#define  GL_AND_INVERTED 142 
#define  GL_AND_REVERSE 141 
#define  GL_CLEAR 140 
#define  GL_COPY 139 
#define  GL_COPY_INVERTED 138 
#define  GL_EQUIV 137 
#define  GL_INVERT 136 
#define  GL_NAND 135 
#define  GL_NOOP 134 
#define  GL_NOR 133 
#define  GL_OR 132 
#define  GL_OR_INVERTED 131 
#define  GL_OR_REVERSE 130 
#define  GL_SET 129 
#define  GL_XOR 128 
 int PB_SIZE ; 
 int /*<<< orphan*/  gl_problem (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  gl_read_alpha_pixels (TYPE_4__*,size_t,int const*,int const*,int*,int*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,size_t,int const*,int const*,int*,int*,int*,int*,int*) ; 

void gl_logicop_rgba_pixels( GLcontext *ctx,
                             GLuint n, const GLint x[], const GLint y[],
                             GLubyte red[], GLubyte green[],
                             GLubyte blue[], GLubyte alpha[],
                             GLubyte mask[] )
{
   GLubyte rdest[PB_SIZE], gdest[PB_SIZE], bdest[PB_SIZE], adest[PB_SIZE];
   GLuint i;

   /* Read pixels from current color buffer */
   (*ctx->Driver.ReadColorPixels)( ctx, n, x, y, rdest, gdest, bdest, adest, mask );
   if (ctx->RasterMask & ALPHABUF_BIT) {
      gl_read_alpha_pixels( ctx, n, x, y, adest, mask );
   }

   /* apply logic op */
   switch (ctx->Color.LogicOp) {
      case GL_CLEAR:
         for (i=0;i<n;i++) {
            if (mask[i]) {
               red[i] = green[i] = blue[i] = alpha[i] = 0;
            }
         }
         break;
      case GL_SET:
         {
            GLubyte r = (GLint) ctx->Visual->RedScale;
            GLubyte g = (GLint) ctx->Visual->GreenScale;
            GLubyte b = (GLint) ctx->Visual->BlueScale;
            GLubyte a = (GLint) ctx->Visual->AlphaScale;
            for (i=0;i<n;i++) {
               if (mask[i]) {
                  red[i]   = r;
                  green[i] = g;
                  blue[i]  = b;
                  alpha[i] = a;
               }
            }
         }
         break;
      case GL_COPY:
         /* do nothing */
         break;
      case GL_COPY_INVERTED:
         for (i=0;i<n;i++) {
            if (mask[i]) {
               red[i]   = ~red[i];
               green[i] = ~green[i];
               blue[i]  = ~blue[i];
               alpha[i] = ~alpha[i];
            }
         }
         break;
      case GL_NOOP:
         for (i=0;i<n;i++) {
            if (mask[i]) {
               red[i]   = rdest[i];
               green[i] = gdest[i];
               blue[i]  = bdest[i];
               alpha[i] = adest[i];
            }
         }
         break;
      case GL_INVERT:
         for (i=0;i<n;i++) {
            if (mask[i]) {
               red[i]   = ~rdest[i];
               green[i] = ~gdest[i];
               blue[i]  = ~bdest[i];
               alpha[i] = ~adest[i];
            }
         }
         break;
      case GL_AND:
         for (i=0;i<n;i++) {
            if (mask[i]) {
               red[i]   &= rdest[i];
               green[i] &= gdest[i];
               blue[i]  &= bdest[i];
               alpha[i] &= adest[i];
            }
         }
         break;
      case GL_NAND:
         for (i=0;i<n;i++) {
            if (mask[i]) {
               red[i]   = ~(red[i]   & rdest[i]);
               green[i] = ~(green[i] & gdest[i]);
               blue[i]  = ~(blue[i]  & bdest[i]);
               alpha[i] = ~(alpha[i] & adest[i]);
            }
         }
         break;
      case GL_OR:
         for (i=0;i<n;i++) {
            if (mask[i]) {
               red[i]   |= rdest[i];
               green[i] |= gdest[i];
               blue[i]  |= bdest[i];
               alpha[i] |= adest[i];
            }
         }
         break;
      case GL_NOR:
         for (i=0;i<n;i++) {
            if (mask[i]) {
               red[i]   = ~(red[i]   | rdest[i]);
               green[i] = ~(green[i] | gdest[i]);
               blue[i]  = ~(blue[i]  | bdest[i]);
               alpha[i] = ~(alpha[i] | adest[i]);
            }
         }
         break;
      case GL_XOR:
         for (i=0;i<n;i++) {
            if (mask[i]) {
               red[i]   ^= rdest[i];
               green[i] ^= gdest[i];
               blue[i]  ^= bdest[i];
               alpha[i] ^= adest[i];
            }
         }
         break;
      case GL_EQUIV:
         for (i=0;i<n;i++) {
            if (mask[i]) {
               red[i]   = ~(red[i]   ^ rdest[i]);
               green[i] = ~(green[i] ^ gdest[i]);
               blue[i]  = ~(blue[i]  ^ bdest[i]);
               alpha[i] = ~(alpha[i] ^ adest[i]);
            }
         }
         break;
      case GL_AND_REVERSE:
         for (i=0;i<n;i++) {
            if (mask[i]) {
               red[i]   = red[i]   & ~rdest[i];
               green[i] = green[i] & ~gdest[i];
               blue[i]  = blue[i]  & ~bdest[i];
               alpha[i] = alpha[i] & ~adest[i];
            }
         }
         break;
      case GL_AND_INVERTED:
         for (i=0;i<n;i++) {
            if (mask[i]) {
               red[i]   = ~red[i]   & rdest[i];
               green[i] = ~green[i] & gdest[i];
               blue[i]  = ~blue[i]  & bdest[i];
               alpha[i] = ~alpha[i] & adest[i];
            }
         }
         break;
      case GL_OR_REVERSE:
         for (i=0;i<n;i++) {
            if (mask[i]) {
               red[i]   = red[i]   | ~rdest[i];
               green[i] = green[i] | ~gdest[i];
               blue[i]  = blue[i]  | ~bdest[i];
               alpha[i] = alpha[i] | ~adest[i];
            }
         }
         break;
      case GL_OR_INVERTED:
         for (i=0;i<n;i++) {
            if (mask[i]) {
               red[i]   = ~red[i]   | rdest[i];
               green[i] = ~green[i] | gdest[i];
               blue[i]  = ~blue[i]  | bdest[i];
               alpha[i] = ~alpha[i] | adest[i];
            }
         }
         break;
      default:
         /* should never happen */
         gl_problem(ctx, "Bad function in gl_logicop_rgba_pixels");
         return;
   }
}