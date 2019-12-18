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
 unsigned short* hf ; 
 int hf_height ; 
 int hf_width ; 
 unsigned short* malloc (int) ; 
 unsigned short* stb_file (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stb_filewrite (char*,unsigned short*,int) ; 
 unsigned short* stbi_load_16 (char*,int*,int*,int*,int) ; 
 int /*<<< orphan*/  stbpg_gl_compat_version (int,int) ; 
 int /*<<< orphan*/  stbpg_run () ; 
 int /*<<< orphan*/  stbpg_windowed (char*,int,int) ; 

void stbpg_main(int argc, char **argv)
{
   int i,j;

   #if 0
   int w,h,c;
   unsigned short *data = stbi_load_16("c:/x/ned_1m/test2.png", &w, &h, &c, 1);
   stb_filewrite("c:/x/ned_1m/x73_y428_10012_10012.bin", data, w*h*2);
   #else
   unsigned short *data = stb_file("c:/x/ned_1m/x73_y428_10012_10012.bin", NULL);
   int w=10012, h = 10012;
   #endif

   hf = malloc(hf_width * hf_height * 4);
   for (j=0; j < hf_height; ++j)
      for (i=0; i < hf_width; ++i)
         hf[j*hf_width+i] = data[j*w+i] / 32.0f;

   stbpg_gl_compat_version(1,1);   
   stbpg_windowed("terrain_edit", 1920, 1080);
   stbpg_run();

   return;
}