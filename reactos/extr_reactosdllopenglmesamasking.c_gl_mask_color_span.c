#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int ColorMask; } ;
struct TYPE_6__ {TYPE_1__ Color; } ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLubyte ;
typedef  int /*<<< orphan*/  GLint ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
 int MAX_WIDTH ; 
 int /*<<< orphan*/  MEMCPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_read_color_span (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void gl_mask_color_span( GLcontext *ctx,
                         GLuint n, GLint x, GLint y,
                         GLubyte red[], GLubyte green[],
                         GLubyte blue[], GLubyte alpha[] )
{
   GLubyte r[MAX_WIDTH], g[MAX_WIDTH], b[MAX_WIDTH], a[MAX_WIDTH];

   gl_read_color_span( ctx, n, x, y, r, g, b, a );

   if ((ctx->Color.ColorMask & 8) == 0) {
      /* replace source reds with frame buffer reds */
      MEMCPY( red, r, n );
   }
   if ((ctx->Color.ColorMask & 4) == 0) {
      /* replace source greens with frame buffer greens */
      MEMCPY( green, g, n );
   }
   if ((ctx->Color.ColorMask & 2) == 0) {
      /* replace source blues with frame buffer blues */
      MEMCPY( blue, b, n );
   }
   if ((ctx->Color.ColorMask & 1) == 0) {
      /* replace source alphas with frame buffer alphas */
      MEMCPY( alpha, a, n );
   }
}