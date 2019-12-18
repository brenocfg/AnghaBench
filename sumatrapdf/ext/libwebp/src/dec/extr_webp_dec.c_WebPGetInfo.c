#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int width; int height; } ;
typedef  TYPE_1__ WebPBitstreamFeatures ;

/* Variables and functions */
 scalar_t__ GetFeatures (int /*<<< orphan*/  const*,size_t,TYPE_1__*) ; 
 scalar_t__ VP8_STATUS_OK ; 

int WebPGetInfo(const uint8_t* data, size_t data_size,
                int* width, int* height) {
  WebPBitstreamFeatures features;

  if (GetFeatures(data, data_size, &features) != VP8_STATUS_OK) {
    return 0;
  }

  if (width != NULL) {
    *width  = features.width;
  }
  if (height != NULL) {
    *height = features.height;
  }

  return 1;
}