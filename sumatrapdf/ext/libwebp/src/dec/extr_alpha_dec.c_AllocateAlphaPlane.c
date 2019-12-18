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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int const uint64_t ;
struct TYPE_5__ {int width; int crop_bottom; } ;
typedef  TYPE_1__ VP8Io ;
struct TYPE_6__ {int /*<<< orphan*/ * alpha_prev_line_; int /*<<< orphan*/ * alpha_plane_mem_; int /*<<< orphan*/ * alpha_plane_; } ;
typedef  TYPE_2__ VP8Decoder ;

/* Variables and functions */
 scalar_t__ WebPSafeMalloc (int const,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int AllocateAlphaPlane(VP8Decoder* const dec, const VP8Io* const io) {
  const int stride = io->width;
  const int height = io->crop_bottom;
  const uint64_t alpha_size = (uint64_t)stride * height;
  assert(dec->alpha_plane_mem_ == NULL);
  dec->alpha_plane_mem_ =
      (uint8_t*)WebPSafeMalloc(alpha_size, sizeof(*dec->alpha_plane_));
  if (dec->alpha_plane_mem_ == NULL) {
    return 0;
  }
  dec->alpha_plane_ = dec->alpha_plane_mem_;
  dec->alpha_prev_line_ = NULL;
  return 1;
}