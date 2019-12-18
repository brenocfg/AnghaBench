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
typedef  int /*<<< orphan*/  VP8LBitReader ;

/* Variables and functions */
 int /*<<< orphan*/  ReadImageInfo (int /*<<< orphan*/ *,int*,int*,int*) ; 
 int /*<<< orphan*/  VP8LCheckSignature (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  VP8LInitBitReader (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 size_t VP8L_FRAME_HEADER_SIZE ; 

int VP8LGetInfo(const uint8_t* data, size_t data_size,
                int* const width, int* const height, int* const has_alpha) {
  if (data == NULL || data_size < VP8L_FRAME_HEADER_SIZE) {
    return 0;         // not enough data
  } else if (!VP8LCheckSignature(data, data_size)) {
    return 0;         // bad signature
  } else {
    int w, h, a;
    VP8LBitReader br;
    VP8LInitBitReader(&br, data, data_size);
    if (!ReadImageInfo(&br, &w, &h, &a)) {
      return 0;
    }
    if (width != NULL) *width = w;
    if (height != NULL) *height = h;
    if (has_alpha != NULL) *has_alpha = a;
    return 1;
  }
}