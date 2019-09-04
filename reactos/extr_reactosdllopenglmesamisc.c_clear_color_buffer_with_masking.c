#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  (* WriteIndexSpan ) (TYPE_6__*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int*) ;int /*<<< orphan*/  (* WriteColorSpan ) (TYPE_6__*,scalar_t__,scalar_t__,scalar_t__,int*,int*,int*,int*,int /*<<< orphan*/ *) ;} ;
struct TYPE_16__ {int* ClearColor; int /*<<< orphan*/  ClearIndex; } ;
struct TYPE_13__ {scalar_t__ Enabled; } ;
struct TYPE_18__ {int RasterMask; TYPE_5__ Driver; TYPE_4__ Color; TYPE_3__* Visual; TYPE_2__* Buffer; TYPE_1__ Scissor; } ;
struct TYPE_15__ {int RedScale; int GreenScale; int BlueScale; int AlphaScale; scalar_t__ RGBAflag; } ;
struct TYPE_14__ {scalar_t__ Xmin; scalar_t__ Ymin; scalar_t__ Ymax; scalar_t__ Xmax; scalar_t__ Height; scalar_t__ Width; } ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int GLubyte ;
typedef  scalar_t__ GLint ;
typedef  TYPE_6__ GLcontext ;

/* Variables and functions */
 int ALPHABUF_BIT ; 
 int MAX_WIDTH ; 
 int /*<<< orphan*/  MEMSET (int*,int,scalar_t__) ; 
 int /*<<< orphan*/  gl_mask_color_span (TYPE_6__*,scalar_t__,scalar_t__,scalar_t__,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  gl_mask_index_span (TYPE_6__*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl_write_alpha_span (TYPE_6__*,scalar_t__,scalar_t__,scalar_t__,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,scalar_t__,scalar_t__,scalar_t__,int*,int*,int*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_6__*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static void clear_color_buffer_with_masking( GLcontext *ctx )
{
   GLint x, y, height, width;

   /* Compute region to clear */
   if (ctx->Scissor.Enabled) {
      x = ctx->Buffer->Xmin;
      y = ctx->Buffer->Ymin;
      height = ctx->Buffer->Ymax - ctx->Buffer->Ymin + 1;
      width  = ctx->Buffer->Xmax - ctx->Buffer->Xmin + 1;
   }
   else {
      x = 0;
      y = 0;
      height = ctx->Buffer->Height;
      width  = ctx->Buffer->Width;
   }

   if (ctx->Visual->RGBAflag) {
      /* RGBA mode */
      GLubyte red[MAX_WIDTH], green[MAX_WIDTH];
      GLubyte blue[MAX_WIDTH], alpha[MAX_WIDTH];
      GLubyte r = ctx->Color.ClearColor[0] * ctx->Visual->RedScale;
      GLubyte g = ctx->Color.ClearColor[1] * ctx->Visual->GreenScale;
      GLubyte b = ctx->Color.ClearColor[2] * ctx->Visual->BlueScale;
      GLubyte a = ctx->Color.ClearColor[3] * ctx->Visual->AlphaScale;
      GLint i;
      for (i=0;i<height;i++,y++) {
         MEMSET( red,   (int) r, width );
         MEMSET( green, (int) g, width );
         MEMSET( blue,  (int) b, width );
         MEMSET( alpha, (int) a, width );
         gl_mask_color_span( ctx, width, x, y, red, green, blue, alpha );
         (*ctx->Driver.WriteColorSpan)( ctx,
                                 width, x, y, red, green, blue, alpha, NULL );
         if (ctx->RasterMask & ALPHABUF_BIT) {
            gl_write_alpha_span( ctx, width, x, y, alpha, NULL );
         }
      }
   }
   else {
      /* Color index mode */
      GLuint indx[MAX_WIDTH];
      GLubyte mask[MAX_WIDTH];
      GLint i, j;
      MEMSET( mask, 1, width );
      for (i=0;i<height;i++,y++) {
         for (j=0;j<width;j++) {
            indx[j] = ctx->Color.ClearIndex;
         }
         gl_mask_index_span( ctx, width, x, y, indx );
         (*ctx->Driver.WriteIndexSpan)( ctx, width, x, y, indx, mask );
      }
   }
}