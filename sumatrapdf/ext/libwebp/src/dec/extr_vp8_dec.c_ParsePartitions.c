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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  VP8StatusCode ;
struct TYPE_3__ {int num_parts_minus_one_; scalar_t__ parts_; int /*<<< orphan*/  br_; } ;
typedef  TYPE_1__ VP8Decoder ;
typedef  int /*<<< orphan*/  VP8BitReader ;

/* Variables and functions */
 int VP8GetValue (int /*<<< orphan*/ * const,int,char*) ; 
 int /*<<< orphan*/  VP8InitBitReader (scalar_t__,int const*,size_t) ; 
 int /*<<< orphan*/  VP8_STATUS_NOT_ENOUGH_DATA ; 
 int /*<<< orphan*/  VP8_STATUS_OK ; 
 int /*<<< orphan*/  VP8_STATUS_SUSPENDED ; 

__attribute__((used)) static VP8StatusCode ParsePartitions(VP8Decoder* const dec,
                                     const uint8_t* buf, size_t size) {
  VP8BitReader* const br = &dec->br_;
  const uint8_t* sz = buf;
  const uint8_t* buf_end = buf + size;
  const uint8_t* part_start;
  size_t size_left = size;
  size_t last_part;
  size_t p;

  dec->num_parts_minus_one_ = (1 << VP8GetValue(br, 2, "global-header")) - 1;
  last_part = dec->num_parts_minus_one_;
  if (size < 3 * last_part) {
    // we can't even read the sizes with sz[]! That's a failure.
    return VP8_STATUS_NOT_ENOUGH_DATA;
  }
  part_start = buf + last_part * 3;
  size_left -= last_part * 3;
  for (p = 0; p < last_part; ++p) {
    size_t psize = sz[0] | (sz[1] << 8) | (sz[2] << 16);
    if (psize > size_left) psize = size_left;
    VP8InitBitReader(dec->parts_ + p, part_start, psize);
    part_start += psize;
    size_left -= psize;
    sz += 3;
  }
  VP8InitBitReader(dec->parts_ + last_part, part_start, size_left);
  return (part_start < buf_end) ? VP8_STATUS_OK :
           VP8_STATUS_SUSPENDED;   // Init is ok, but there's not enough data
}