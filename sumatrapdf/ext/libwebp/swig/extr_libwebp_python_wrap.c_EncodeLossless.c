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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t (* WebPEncodeLosslessFunction ) (int /*<<< orphan*/  const*,int,int,int,int /*<<< orphan*/ **) ;

/* Variables and functions */

__attribute__((used)) static uint8_t* EncodeLossless(const uint8_t* rgb,
                               int width, int height, int stride,
                               WebPEncodeLosslessFunction encfn,
                               int* output_size, int* unused) {
  uint8_t* output = NULL;
  const size_t image_size = encfn(rgb, width, height, stride, &output);
  // the values of the following two will be interpreted by
  // ReturnedBufferSize() as 'width' and 'height' in the size calculation.
  *output_size = image_size;
  *unused = 1;
  return image_size ? output : NULL;
}