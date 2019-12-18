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

__attribute__((used)) static void Help(void) {
  printf("Usage: anim_diff <image1> <image2> [options]\n");
  printf("\nOptions:\n");
  printf("  -dump_frames <folder> dump decoded frames in PAM format\n");
  printf("  -min_psnr <float> ... minimum per-frame PSNR\n");
  printf("  -raw_comparison ..... if this flag is not used, RGB is\n");
  printf("                        premultiplied before comparison\n");
  printf("  -max_diff <int> ..... maximum allowed difference per channel\n"
         "                        between corresponding pixels in subsequent\n"
         "                        frames\n");
  printf("  -h .................. this help\n");
  printf("  -version ............ print version number and exit\n");
}