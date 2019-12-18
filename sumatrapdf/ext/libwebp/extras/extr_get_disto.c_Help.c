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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void Help(void) {
  fprintf(stderr,
          "Usage: get_disto [-ssim][-psnr][-alpha] compressed.webp orig.webp\n"
          "  -ssim ..... print SSIM distortion\n"
          "  -psnr ..... print PSNR distortion (default)\n"
          "  -alpha .... preserve alpha plane\n"
          "  -h ........ this message\n"
          "  -o <file> . save the diff map as a WebP lossless file\n"
          "  -scale .... scale the difference map to fit [0..255] range\n"
          "  -gray ..... use grayscale for difference map (-scale)\n"
          " Also handles PNG, JPG and TIFF files, in addition to WebP.\n");
}