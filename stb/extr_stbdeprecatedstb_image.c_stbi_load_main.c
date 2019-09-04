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
 unsigned char* epuc (char*,char*) ; 
 unsigned char* hdr_to_ldr (float*,int,int,int) ; 
 unsigned char* stbi_bmp_load (int /*<<< orphan*/ *,int*,int*,int*,int) ; 
 scalar_t__ stbi_bmp_test (int /*<<< orphan*/ *) ; 
 unsigned char* stbi_gif_load (int /*<<< orphan*/ *,int*,int*,int*,int) ; 
 scalar_t__ stbi_gif_test (int /*<<< orphan*/ *) ; 
 float* stbi_hdr_load (int /*<<< orphan*/ *,int*,int*,int*,int) ; 
 scalar_t__ stbi_hdr_test (int /*<<< orphan*/ *) ; 
 unsigned char* stbi_jpeg_load (int /*<<< orphan*/ *,int*,int*,int*,int) ; 
 scalar_t__ stbi_jpeg_test (int /*<<< orphan*/ *) ; 
 unsigned char* stbi_pic_load (int /*<<< orphan*/ *,int*,int*,int*,int) ; 
 scalar_t__ stbi_pic_test (int /*<<< orphan*/ *) ; 
 unsigned char* stbi_png_load (int /*<<< orphan*/ *,int*,int*,int*,int) ; 
 scalar_t__ stbi_png_test (int /*<<< orphan*/ *) ; 
 unsigned char* stbi_psd_load (int /*<<< orphan*/ *,int*,int*,int*,int) ; 
 scalar_t__ stbi_psd_test (int /*<<< orphan*/ *) ; 
 unsigned char* stbi_tga_load (int /*<<< orphan*/ *,int*,int*,int*,int) ; 
 scalar_t__ stbi_tga_test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned char *stbi_load_main(stbi *s, int *x, int *y, int *comp, int req_comp)
{
   if (stbi_jpeg_test(s)) return stbi_jpeg_load(s,x,y,comp,req_comp);
   if (stbi_png_test(s))  return stbi_png_load(s,x,y,comp,req_comp);
   if (stbi_bmp_test(s))  return stbi_bmp_load(s,x,y,comp,req_comp);
   if (stbi_gif_test(s))  return stbi_gif_load(s,x,y,comp,req_comp);
   if (stbi_psd_test(s))  return stbi_psd_load(s,x,y,comp,req_comp);
   if (stbi_pic_test(s))  return stbi_pic_load(s,x,y,comp,req_comp);

   #ifndef STBI_NO_HDR
   if (stbi_hdr_test(s)) {
      float *hdr = stbi_hdr_load(s, x,y,comp,req_comp);
      return hdr_to_ldr(hdr, *x, *y, req_comp ? req_comp : *comp);
   }
   #endif

   // test tga last because it's a crappy test!
   if (stbi_tga_test(s))
      return stbi_tga_load(s,x,y,comp,req_comp);
   return epuc("unknown image type", "Image not of any known type, or corrupt");
}