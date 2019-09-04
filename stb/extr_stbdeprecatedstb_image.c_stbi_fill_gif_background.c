#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t bgindex; int w; int h; int /*<<< orphan*/ * out; int /*<<< orphan*/ ** pal; } ;
typedef  TYPE_1__ stbi_gif ;
typedef  int /*<<< orphan*/  stbi__uint8 ;

/* Variables and functions */

__attribute__((used)) static void stbi_fill_gif_background(stbi_gif *g)
{
   int i;
   stbi__uint8 *c = g->pal[g->bgindex];
   // @OPTIMIZE: write a dword at a time
   for (i = 0; i < g->w * g->h * 4; i += 4) {
      stbi__uint8 *p  = &g->out[i];
      p[0] = c[2];
      p[1] = c[1];
      p[2] = c[0];
      p[3] = c[3];
   }
}