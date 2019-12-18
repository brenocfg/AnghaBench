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
typedef  int /*<<< orphan*/  stbtt_pack_context ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_H ; 
 int /*<<< orphan*/  BITMAP_W ; 
 int /*<<< orphan*/  GL_ALPHA ; 
 int /*<<< orphan*/  GL_LINEAR ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_MAG_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_MIN_FILTER ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 scalar_t__* chardata ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  font_tex ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fread (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGenTextures (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glTexImage2D (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glTexParameteri (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * scale ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 char* stb_wingraph_commandline ; 
 int /*<<< orphan*/  stbtt_PackBegin (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stbtt_PackEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stbtt_PackFontRange (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,scalar_t__) ; 
 int /*<<< orphan*/  stbtt_PackSetOversampling (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * temp_bitmap ; 
 int /*<<< orphan*/  ttf_buffer ; 

void load_fonts(void)
{
   stbtt_pack_context pc;
   int i;
   FILE *f;
   char filename[256];
   char *win = getenv("windir");
   if (win == NULL) win = getenv("SystemRoot");

   f = fopen(stb_wingraph_commandline, "rb");
   if (!f) {
      if (win == NULL)
         sprintf(filename, "arial.ttf", win);
      else
         sprintf(filename, "%s/fonts/arial.ttf", win);
      f = fopen(filename, "rb");
      if (!f) exit(0);
   }

   fread(ttf_buffer, 1, 1<<25, f);

   stbtt_PackBegin(&pc, temp_bitmap[0], BITMAP_W, BITMAP_H, 0, 1, NULL);
   for (i=0; i < 2; ++i) {
      stbtt_PackSetOversampling(&pc, 1, 1);
      stbtt_PackFontRange(&pc, ttf_buffer, 0, scale[i], 32, 95, chardata[i*3+0]+32);
      stbtt_PackSetOversampling(&pc, 2, 2);
      stbtt_PackFontRange(&pc, ttf_buffer, 0, scale[i], 32, 95, chardata[i*3+1]+32);
      stbtt_PackSetOversampling(&pc, 3, 1);
      stbtt_PackFontRange(&pc, ttf_buffer, 0, scale[i], 32, 95, chardata[i*3+2]+32);
   }
   stbtt_PackEnd(&pc);

   glGenTextures(1, &font_tex);
   glBindTexture(GL_TEXTURE_2D, font_tex);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, BITMAP_W, BITMAP_H, 0, GL_ALPHA, GL_UNSIGNED_BYTE, temp_bitmap);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}