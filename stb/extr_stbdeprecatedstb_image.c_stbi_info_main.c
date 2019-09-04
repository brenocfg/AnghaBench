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
typedef  int /*<<< orphan*/  stbi ;

/* Variables and functions */
 int e (char*,char*) ; 
 scalar_t__ stbi_bmp_info (int /*<<< orphan*/ *,int*,int*,int*) ; 
 scalar_t__ stbi_gif_info (int /*<<< orphan*/ *,int*,int*,int*) ; 
 scalar_t__ stbi_hdr_info (int /*<<< orphan*/ *,int*,int*,int*) ; 
 scalar_t__ stbi_jpeg_info (int /*<<< orphan*/ *,int*,int*,int*) ; 
 scalar_t__ stbi_pic_info (int /*<<< orphan*/ *,int*,int*,int*) ; 
 scalar_t__ stbi_png_info (int /*<<< orphan*/ *,int*,int*,int*) ; 
 scalar_t__ stbi_psd_info (int /*<<< orphan*/ *,int*,int*,int*) ; 
 scalar_t__ stbi_tga_info (int /*<<< orphan*/ *,int*,int*,int*) ; 

__attribute__((used)) static int stbi_info_main(stbi *s, int *x, int *y, int *comp)
{
   if (stbi_jpeg_info(s, x, y, comp))
       return 1;
   if (stbi_png_info(s, x, y, comp))
       return 1;
   if (stbi_gif_info(s, x, y, comp))
       return 1;
   if (stbi_bmp_info(s, x, y, comp))
       return 1;
   if (stbi_psd_info(s, x, y, comp))
       return 1;
   if (stbi_pic_info(s, x, y, comp))
       return 1;
   #ifndef STBI_NO_HDR
   if (stbi_hdr_info(s, x, y, comp))
       return 1;
   #endif
   // test tga last because it's a crappy test!
   if (stbi_tga_info(s, x, y, comp))
       return 1;
   return e("unknown image type", "Image not of any known type, or corrupt");
}