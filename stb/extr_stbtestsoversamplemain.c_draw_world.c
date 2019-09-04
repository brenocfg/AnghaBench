#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 scalar_t__ BITMAP_H ; 
 scalar_t__ BITMAP_W ; 
 int /*<<< orphan*/  GL_BLEND ; 
 int /*<<< orphan*/  GL_MODELVIEW ; 
 int /*<<< orphan*/  GL_ONE_MINUS_SRC_ALPHA ; 
 int /*<<< orphan*/  GL_QUADS ; 
 int /*<<< orphan*/  GL_SRC_ALPHA ; 
 scalar_t__ black_on_white ; 
 int /*<<< orphan*/  drawBoxTC (int,int,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ fmod (int,int) ; 
 size_t font ; 
 int /*<<< orphan*/  glBegin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBlendFunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glColor3f (int,int,int) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnd () ; 
 int /*<<< orphan*/  glMatrixMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glRotatef (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glTranslatef (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ integer_align ; 
 int /*<<< orphan*/  print (float,int,size_t,char*) ; 
 int rotate_t ; 
 scalar_t__ rotating ; 
 int* sf ; 
 scalar_t__ show_tex ; 
 int translate_t ; 
 scalar_t__ translating ; 

void draw_world(void)
{
   int sfont = sf[font];
   float x = 20;
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   if (black_on_white)
      glColor3f(0,0,0);
   else
      glColor3f(1,1,1);


   print(80, 30, sfont, "Controls:");
   print(100, 60, sfont, "S: toggle font size");
   print(100, 85, sfont, "O: toggle oversampling");
   print(100,110, sfont, "T: toggle translation");
   print(100,135, sfont, "R: toggle rotation");
   print(100,160, sfont, "P: toggle pixel-snap (only non-oversampled)");
   print(100,185, sfont, "G: toggle srgb gamma-correction");
   if (black_on_white)
      print(100,210, sfont, "B: toggle to white-on-black");
   else
      print(100,210, sfont, "B: toggle to black-on-white");
   print(100,235, sfont, "V: view font texture");

   print(80, 300, sfont, "Current font:");

   if (!show_tex) {
      if (font < 3)
         print(100, 350, sfont, "Font height: 24 pixels");
      else
         print(100, 350, sfont, "Font height: 14 pixels");
   }

   if (font%3==1)
      print(100, 325, sfont, "2x2 oversampled text at 1:1");
   else if (font%3 == 2)
      print(100, 325, sfont, "3x1 oversampled text at 1:1");
   else if (integer_align)
      print(100, 325, sfont, "1:1 text, one texel = one pixel, snapped to integer coordinates");
   else
      print(100, 325, sfont, "1:1 text, one texel = one pixel");

   if (show_tex) {
      glBegin(GL_QUADS);
      drawBoxTC(200,400, 200+BITMAP_W,300+BITMAP_H, 0,0,1,1);
      glEnd();
   } else {
      glMatrixMode(GL_MODELVIEW);
      glTranslatef(200,350,0);

      if (translating)
         x += fmod(translate_t*8,30);

      if (rotating) {
         glTranslatef(100,150,0);
         glRotatef(rotate_t*2,0,0,1);
         glTranslatef(-100,-150,0);
      }
      print(x,100, font, "This is a test");
      print(x,130, font, "Now is the time for all good men to come to the aid of their country.");
      print(x,160, font, "The quick brown fox jumps over the lazy dog.");
      print(x,190, font, "0123456789");
   }
}