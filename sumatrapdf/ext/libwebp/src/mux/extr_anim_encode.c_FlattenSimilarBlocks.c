#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {scalar_t__ width; scalar_t__ height; int* argb; int argb_stride; } ;
typedef  TYPE_1__ WebPPicture ;
struct TYPE_7__ {int const y_offset_; int const height_; int const x_offset_; int const width_; } ;
typedef  TYPE_2__ FrameRectangle ;

/* Variables and functions */
 scalar_t__ PixelsAreSimilar (int const,int,int const) ; 
 int QualityToMaxDiff (float) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int FlattenSimilarBlocks(const WebPPicture* const src,
                                const FrameRectangle* const rect,
                                WebPPicture* const dst, float quality) {
  const int max_allowed_diff_lossy = QualityToMaxDiff(quality);
  int i, j;
  int modified = 0;
  const int block_size = 8;
  const int y_start = (rect->y_offset_ + block_size) & ~(block_size - 1);
  const int y_end = (rect->y_offset_ + rect->height_) & ~(block_size - 1);
  const int x_start = (rect->x_offset_ + block_size) & ~(block_size - 1);
  const int x_end = (rect->x_offset_ + rect->width_) & ~(block_size - 1);
  assert(src != NULL && dst != NULL && rect != NULL);
  assert(src->width == dst->width && src->height == dst->height);
  assert((block_size & (block_size - 1)) == 0);  // must be a power of 2
  // Iterate over each block and count similar pixels.
  for (j = y_start; j < y_end; j += block_size) {
    for (i = x_start; i < x_end; i += block_size) {
      int cnt = 0;
      int avg_r = 0, avg_g = 0, avg_b = 0;
      int x, y;
      const uint32_t* const psrc = src->argb + j * src->argb_stride + i;
      uint32_t* const pdst = dst->argb + j * dst->argb_stride + i;
      for (y = 0; y < block_size; ++y) {
        for (x = 0; x < block_size; ++x) {
          const uint32_t src_pixel = psrc[x + y * src->argb_stride];
          const int alpha = src_pixel >> 24;
          if (alpha == 0xff &&
              PixelsAreSimilar(src_pixel, pdst[x + y * dst->argb_stride],
                               max_allowed_diff_lossy)) {
            ++cnt;
            avg_r += (src_pixel >> 16) & 0xff;
            avg_g += (src_pixel >> 8) & 0xff;
            avg_b += (src_pixel >> 0) & 0xff;
          }
        }
      }
      // If we have a fully similar block, we replace it with an
      // average transparent block. This compresses better in lossy mode.
      if (cnt == block_size * block_size) {
        const uint32_t color = (0x00          << 24) |
                               ((avg_r / cnt) << 16) |
                               ((avg_g / cnt) <<  8) |
                               ((avg_b / cnt) <<  0);
        for (y = 0; y < block_size; ++y) {
          for (x = 0; x < block_size; ++x) {
            pdst[x + y * dst->argb_stride] = color;
          }
        }
        modified = 1;
      }
    }
  }
  return modified;
}