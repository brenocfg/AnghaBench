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
struct TYPE_4__ {int /*<<< orphan*/  format; int /*<<< orphan*/  has_animation; int /*<<< orphan*/  has_alpha; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_1__ WebPBitstreamFeatures ;
typedef  int /*<<< orphan*/  VP8StatusCode ;

/* Variables and functions */
 int /*<<< orphan*/  DefaultFeatures (TYPE_1__* const) ; 
 int /*<<< orphan*/  ParseHeadersInternal (int /*<<< orphan*/  const* const,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VP8_STATUS_INVALID_PARAM ; 

__attribute__((used)) static VP8StatusCode GetFeatures(const uint8_t* const data, size_t data_size,
                                 WebPBitstreamFeatures* const features) {
  if (features == NULL || data == NULL) {
    return VP8_STATUS_INVALID_PARAM;
  }
  DefaultFeatures(features);

  // Only parse enough of the data to retrieve the features.
  return ParseHeadersInternal(data, data_size,
                              &features->width, &features->height,
                              &features->has_alpha, &features->has_animation,
                              &features->format, NULL);
}