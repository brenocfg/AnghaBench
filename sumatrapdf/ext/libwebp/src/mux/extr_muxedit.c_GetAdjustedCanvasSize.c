#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int width_; int height_; struct TYPE_5__* next_; int /*<<< orphan*/ * header_; int /*<<< orphan*/ * img_; } ;
typedef  TYPE_1__ WebPMuxImage ;
typedef  scalar_t__ WebPMuxError ;
struct TYPE_6__ {TYPE_1__* images_; } ;
typedef  TYPE_2__ WebPMux ;

/* Variables and functions */
 scalar_t__ GetImageInfo (TYPE_1__*,int*,int*,int*,int*,int*) ; 
 int MAX_POSITION_OFFSET ; 
 scalar_t__ const WEBP_MUX_OK ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static WebPMuxError GetAdjustedCanvasSize(const WebPMux* const mux,
                                          int* const width, int* const height) {
  WebPMuxImage* wpi = NULL;
  assert(mux != NULL);
  assert(width != NULL && height != NULL);

  wpi = mux->images_;
  assert(wpi != NULL);
  assert(wpi->img_ != NULL);

  if (wpi->next_ != NULL) {
    int max_x = 0, max_y = 0;
    // if we have a chain of wpi's, header_ is necessarily set
    assert(wpi->header_ != NULL);
    // Aggregate the bounding box for animation frames.
    for (; wpi != NULL; wpi = wpi->next_) {
      int x_offset = 0, y_offset = 0, duration = 0, w = 0, h = 0;
      const WebPMuxError err = GetImageInfo(wpi, &x_offset, &y_offset,
                                            &duration, &w, &h);
      const int max_x_pos = x_offset + w;
      const int max_y_pos = y_offset + h;
      if (err != WEBP_MUX_OK) return err;
      assert(x_offset < MAX_POSITION_OFFSET);
      assert(y_offset < MAX_POSITION_OFFSET);

      if (max_x_pos > max_x) max_x = max_x_pos;
      if (max_y_pos > max_y) max_y = max_y_pos;
    }
    *width = max_x;
    *height = max_y;
  } else {
    // For a single image, canvas dimensions are same as image dimensions.
    *width = wpi->width_;
    *height = wpi->height_;
  }
  return WEBP_MUX_OK;
}