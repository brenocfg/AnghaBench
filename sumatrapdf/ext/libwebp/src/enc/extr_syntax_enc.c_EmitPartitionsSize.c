#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_7__ {int (* writer ) (size_t*,int,TYPE_1__* const) ;} ;
typedef  TYPE_1__ WebPPicture ;
struct TYPE_8__ {int num_parts_; scalar_t__ parts_; } ;
typedef  TYPE_2__ VP8Encoder ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_NUM_PARTITIONS ; 
 size_t VP8BitWriterSize (scalar_t__) ; 
 int /*<<< orphan*/  VP8_ENC_ERROR_PARTITION_OVERFLOW ; 
 size_t const VP8_MAX_PARTITION_SIZE ; 
 int WebPEncodingSetError (TYPE_1__* const,int /*<<< orphan*/ ) ; 
 int stub1 (size_t*,int,TYPE_1__* const) ; 

__attribute__((used)) static int EmitPartitionsSize(const VP8Encoder* const enc,
                              WebPPicture* const pic) {
  uint8_t buf[3 * (MAX_NUM_PARTITIONS - 1)];
  int p;
  for (p = 0; p < enc->num_parts_ - 1; ++p) {
    const size_t part_size = VP8BitWriterSize(enc->parts_ + p);
    if (part_size >= VP8_MAX_PARTITION_SIZE) {
      return WebPEncodingSetError(pic, VP8_ENC_ERROR_PARTITION_OVERFLOW);
    }
    buf[3 * p + 0] = (part_size >>  0) & 0xff;
    buf[3 * p + 1] = (part_size >>  8) & 0xff;
    buf[3 * p + 2] = (part_size >> 16) & 0xff;
  }
  return p ? pic->writer(buf, 3 * p, pic) : 1;
}