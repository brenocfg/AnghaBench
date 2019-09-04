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
struct TYPE_3__ {int /*<<< orphan*/  t1; int /*<<< orphan*/  s1; int /*<<< orphan*/  t0; int /*<<< orphan*/  s0; int /*<<< orphan*/  y1; int /*<<< orphan*/  x1; int /*<<< orphan*/  y0; int /*<<< orphan*/  x0; } ;
typedef  TYPE_1__ stbtt_aligned_quad ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_H ; 
 int /*<<< orphan*/  BITMAP_W ; 
 int /*<<< orphan*/  GL_QUADS ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/ * chardata ; 
 int /*<<< orphan*/  drawBoxTC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  font_tex ; 
 int /*<<< orphan*/  glBegin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnd () ; 
 int /*<<< orphan*/  integer_align ; 
 int /*<<< orphan*/  stbtt_GetPackedQuad (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*,float*,TYPE_1__*,int /*<<< orphan*/ ) ; 

void print(float x, float y, int font, char *text)
{
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, font_tex);
   glBegin(GL_QUADS);
   while (*text) {
      stbtt_aligned_quad q;
      stbtt_GetPackedQuad(chardata[font], BITMAP_W, BITMAP_H, *text++, &x, &y, &q, font ? 0 : integer_align);
      drawBoxTC(q.x0,q.y0,q.x1,q.y1, q.s0,q.t0,q.s1,q.t1);
   }
   glEnd();
}