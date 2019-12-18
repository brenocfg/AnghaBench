#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_4__ {int use_argb; int* argb; int height; int width; int /*<<< orphan*/  argb_stride; int /*<<< orphan*/  colorspace; } ;
typedef  TYPE_1__ WebPPicture ;

/* Variables and functions */
 int /*<<< orphan*/  WEBP_YUV420 ; 
 int /*<<< orphan*/  WebPPictureAlloc (TYPE_1__*) ; 

int WebPImportRGB565(const uint8_t* rgb565, WebPPicture* pic) {
  int x, y;
  uint32_t* dst;
  if (pic == NULL || rgb565 == NULL) return 0;
  pic->colorspace = WEBP_YUV420;
  pic->use_argb = 1;
  if (!WebPPictureAlloc(pic)) return 0;
  dst = pic->argb;
  for (y = 0; y < pic->height; ++y) {
    const int width = pic->width;
    for (x = 0; x < width; ++x) {
#ifdef WEBP_SWAP_16BIT_CSP
      const uint32_t rg = rgb565[2 * x + 1];
      const uint32_t gb = rgb565[2 * x + 0];
#else
      const uint32_t rg = rgb565[2 * x + 0];
      const uint32_t gb = rgb565[2 * x + 1];
#endif
      uint32_t r = rg & 0xf8;
      uint32_t g = ((rg << 5) | (gb >> 3)) & 0xfc;
      uint32_t b = (gb << 5);
      // dithering
      r = r | (r >> 5);
      g = g | (g >> 6);
      b = b | (b >> 5);
      dst[x] = (0xffu << 24) | (r << 16) | (g << 8) | b;
    }
    rgb565 += 2 * width;
    dst += pic->argb_stride;
  }
  return 1;
}