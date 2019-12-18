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
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void PrintHelp(void) {
  printf("Usage: webpmux -get GET_OPTIONS INPUT -o OUTPUT\n");
  printf("       webpmux -set SET_OPTIONS INPUT -o OUTPUT\n");
  printf("       webpmux -duration DURATION_OPTIONS [-duration ...]\n");
  printf("               INPUT -o OUTPUT\n");
  printf("       webpmux -strip STRIP_OPTIONS INPUT -o OUTPUT\n");
  printf("       webpmux -frame FRAME_OPTIONS [-frame...] [-loop LOOP_COUNT]"
         "\n");
  printf("               [-bgcolor BACKGROUND_COLOR] -o OUTPUT\n");
  printf("       webpmux -info INPUT\n");
  printf("       webpmux [-h|-help]\n");
  printf("       webpmux -version\n");
  printf("       webpmux argument_file_name\n");

  printf("\n");
  printf("GET_OPTIONS:\n");
  printf(" Extract relevant data:\n");
  printf("   icc       get ICC profile\n");
  printf("   exif      get EXIF metadata\n");
  printf("   xmp       get XMP metadata\n");
  printf("   frame n   get nth frame\n");

  printf("\n");
  printf("SET_OPTIONS:\n");
  printf(" Set color profile/metadata:\n");
  printf("   icc  file.icc     set ICC profile\n");
  printf("   exif file.exif    set EXIF metadata\n");
  printf("   xmp  file.xmp     set XMP metadata\n");
  printf("   where:    'file.icc' contains the ICC profile to be set,\n");
  printf("             'file.exif' contains the EXIF metadata to be set\n");
  printf("             'file.xmp' contains the XMP metadata to be set\n");

  printf("\n");
  printf("DURATION_OPTIONS:\n");
  printf(" Set duration of selected frames:\n");
  printf("   duration            set duration for each frames\n");
  printf("   duration,frame      set duration of a particular frame\n");
  printf("   duration,start,end  set duration of frames in the\n");
  printf("                        interval [start,end])\n");
  printf("   where: 'duration' is the duration in milliseconds\n");
  printf("          'start' is the start frame index\n");
  printf("          'end' is the inclusive end frame index\n");
  printf("           The special 'end' value '0' means: last frame.\n");

  printf("\n");
  printf("STRIP_OPTIONS:\n");
  printf(" Strip color profile/metadata:\n");
  printf("   icc       strip ICC profile\n");
  printf("   exif      strip EXIF metadata\n");
  printf("   xmp       strip XMP metadata\n");

  printf("\n");
  printf("FRAME_OPTIONS(i):\n");
  printf(" Create animation:\n");
  printf("   file_i +di+[xi+yi[+mi[bi]]]\n");
  printf("   where:    'file_i' is the i'th animation frame (WebP format),\n");
  printf("             'di' is the pause duration before next frame,\n");
  printf("             'xi','yi' specify the image offset for this frame,\n");
  printf("             'mi' is the dispose method for this frame (0 or 1),\n");
  printf("             'bi' is the blending method for this frame (+b or -b)"
         "\n");

  printf("\n");
  printf("LOOP_COUNT:\n");
  printf(" Number of times to repeat the animation.\n");
  printf(" Valid range is 0 to 65535 [Default: 0 (infinite)].\n");

  printf("\n");
  printf("BACKGROUND_COLOR:\n");
  printf(" Background color of the canvas.\n");
  printf("  A,R,G,B\n");
  printf("  where:    'A', 'R', 'G' and 'B' are integers in the range 0 to 255 "
         "specifying\n");
  printf("            the Alpha, Red, Green and Blue component values "
         "respectively\n");
  printf("            [Default: 255,255,255,255]\n");

  printf("\nINPUT & OUTPUT are in WebP format.\n");

  printf("\nNote: The nature of EXIF, XMP and ICC data is not checked");
  printf(" and is assumed to be\nvalid.\n");
  printf("\nNote: if a single file name is passed as the argument, the "
         "arguments will be\n");
  printf("tokenized from this file. The file name must not start with "
         "the character '-'.\n");
}