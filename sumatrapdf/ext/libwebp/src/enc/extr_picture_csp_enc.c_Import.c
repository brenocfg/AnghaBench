#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int width; int height; int /*<<< orphan*/  argb_stride; int /*<<< orphan*/ * argb; int /*<<< orphan*/  use_argb; } ;
typedef  TYPE_1__ WebPPicture ;

/* Variables and functions */
 int ALPHA_OFFSET ; 
 int ImportYUVAFromRGBA (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int,float,int /*<<< orphan*/ ,TYPE_1__* const) ; 
 int /*<<< orphan*/  VP8LConvertBGRAToRGBA (int /*<<< orphan*/  const*,int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VP8LDspInit () ; 
 int /*<<< orphan*/  WebPInitAlphaProcessing () ; 
 int /*<<< orphan*/  WebPPackARGB (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WebPPackRGB (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int const,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WebPPictureAlloc (TYPE_1__* const) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int const) ; 

__attribute__((used)) static int Import(WebPPicture* const picture,
                  const uint8_t* rgb, int rgb_stride,
                  int step, int swap_rb, int import_alpha) {
  int y;
  // swap_rb -> b,g,r,a , !swap_rb -> r,g,b,a
  const uint8_t* r_ptr = rgb + (swap_rb ? 2 : 0);
  const uint8_t* g_ptr = rgb + 1;
  const uint8_t* b_ptr = rgb + (swap_rb ? 0 : 2);
  const int width = picture->width;
  const int height = picture->height;

  if (!picture->use_argb) {
    const uint8_t* a_ptr = import_alpha ? rgb + 3 : NULL;
    return ImportYUVAFromRGBA(r_ptr, g_ptr, b_ptr, a_ptr, step, rgb_stride,
                              0.f /* no dithering */, 0, picture);
  }
  if (!WebPPictureAlloc(picture)) return 0;

  VP8LDspInit();
  WebPInitAlphaProcessing();

  if (import_alpha) {
    // dst[] byte order is {a,r,g,b} for big-endian, {b,g,r,a} for little endian
    uint32_t* dst = picture->argb;
    const int do_copy = (ALPHA_OFFSET == 3) && swap_rb;
    assert(step == 4);
    if (do_copy) {
      for (y = 0; y < height; ++y) {
        memcpy(dst, rgb, width * 4);
        rgb += rgb_stride;
        dst += picture->argb_stride;
      }
    } else {
      for (y = 0; y < height; ++y) {
#ifdef WORDS_BIGENDIAN
        // BGRA or RGBA input order.
        const uint8_t* a_ptr = rgb + 3;
        WebPPackARGB(a_ptr, r_ptr, g_ptr, b_ptr, width, dst);
        r_ptr += rgb_stride;
        g_ptr += rgb_stride;
        b_ptr += rgb_stride;
#else
        // RGBA input order. Need to swap R and B.
        VP8LConvertBGRAToRGBA((const uint32_t*)rgb, width, (uint8_t*)dst);
#endif
        rgb += rgb_stride;
        dst += picture->argb_stride;
      }
    }
  } else {
    uint32_t* dst = picture->argb;
    assert(step >= 3);
    for (y = 0; y < height; ++y) {
      WebPPackRGB(r_ptr, g_ptr, b_ptr, width, step, dst);
      r_ptr += rgb_stride;
      g_ptr += rgb_stride;
      b_ptr += rgb_stride;
      dst += picture->argb_stride;
    }
  }
  return 1;
}