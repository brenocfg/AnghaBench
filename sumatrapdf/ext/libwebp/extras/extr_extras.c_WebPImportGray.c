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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int width; int height; int y_stride; int uv_stride; scalar_t__ v; scalar_t__ u; scalar_t__ y; int /*<<< orphan*/  colorspace; } ;
typedef  TYPE_1__ WebPPicture ;

/* Variables and functions */
 int /*<<< orphan*/  WEBP_YUV420 ; 
 int /*<<< orphan*/  WebPPictureAlloc (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int,int) ; 

int WebPImportGray(const uint8_t* gray_data, WebPPicture* pic) {
  int y, width, uv_width;
  if (pic == NULL || gray_data == NULL) return 0;
  pic->colorspace = WEBP_YUV420;
  if (!WebPPictureAlloc(pic)) return 0;
  width = pic->width;
  uv_width = (width + 1) >> 1;
  for (y = 0; y < pic->height; ++y) {
    memcpy(pic->y + y * pic->y_stride, gray_data, width);
    gray_data += width;    // <- we could use some 'data_stride' here if needed
    if ((y & 1) == 0) {
      memset(pic->u + (y >> 1) * pic->uv_stride, 128, uv_width);
      memset(pic->v + (y >> 1) * pic->uv_stride, 128, uv_width);
    }
  }
  return 1;
}