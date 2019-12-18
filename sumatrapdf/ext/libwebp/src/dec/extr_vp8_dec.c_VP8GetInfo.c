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
typedef  int uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  VP8CheckSignature (int const*,size_t) ; 
 size_t VP8_FRAME_HEADER_SIZE ; 

int VP8GetInfo(const uint8_t* data, size_t data_size, size_t chunk_size,
               int* const width, int* const height) {
  if (data == NULL || data_size < VP8_FRAME_HEADER_SIZE) {
    return 0;         // not enough data
  }
  // check signature
  if (!VP8CheckSignature(data + 3, data_size - 3)) {
    return 0;         // Wrong signature.
  } else {
    const uint32_t bits = data[0] | (data[1] << 8) | (data[2] << 16);
    const int key_frame = !(bits & 1);
    const int w = ((data[7] << 8) | data[6]) & 0x3fff;
    const int h = ((data[9] << 8) | data[8]) & 0x3fff;

    if (!key_frame) {   // Not a keyframe.
      return 0;
    }

    if (((bits >> 1) & 7) > 3) {
      return 0;         // unknown profile
    }
    if (!((bits >> 4) & 1)) {
      return 0;         // first frame is invisible!
    }
    if (((bits >> 5)) >= chunk_size) {  // partition_length
      return 0;         // inconsistent size information.
    }
    if (w == 0 || h == 0) {
      return 0;         // We don't support both width and height to be zero.
    }

    if (width) {
      *width = w;
    }
    if (height) {
      *height = h;
    }

    return 1;
  }
}