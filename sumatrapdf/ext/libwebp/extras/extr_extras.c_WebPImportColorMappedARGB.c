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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int width; int use_argb; int height; int /*<<< orphan*/  argb_stride; int /*<<< orphan*/ * argb; } ;
typedef  TYPE_1__ WebPPicture ;

/* Variables and functions */
 int MAX_PALETTE_SIZE ; 
 int /*<<< orphan*/  WebPPictureAlloc (TYPE_1__*) ; 
 int /*<<< orphan*/  WebPPictureFree (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 

int WebPImportColorMappedARGB(const uint8_t* indexed, int indexed_stride,
                              const uint32_t palette[], int palette_size,
                              WebPPicture* pic) {
  int x, y;
  uint32_t* dst;
  // 256 as the input buffer is uint8_t.
  assert(MAX_PALETTE_SIZE <= 256);
  if (pic == NULL || indexed == NULL || indexed_stride < pic->width ||
      palette == NULL || palette_size > MAX_PALETTE_SIZE || palette_size <= 0) {
    return 0;
  }
  pic->use_argb = 1;
  if (!WebPPictureAlloc(pic)) return 0;
  dst = pic->argb;
  for (y = 0; y < pic->height; ++y) {
    for (x = 0; x < pic->width; ++x) {
      // Make sure we are within the palette.
      if (indexed[x] >= palette_size) {
        WebPPictureFree(pic);
        return 0;
      }
      dst[x] = palette[indexed[x]];
    }
    indexed += indexed_stride;
    dst += pic->argb_stride;
  }
  return 1;
}