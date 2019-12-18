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
struct TYPE_4__ {int base_quant_; int const mb_w_; int const mb_h_; int const num_parts_; int /*<<< orphan*/  pic_; scalar_t__ parts_; } ;
typedef  TYPE_1__ VP8Encoder ;

/* Variables and functions */
 int VP8BitWriterInit (scalar_t__,int const) ; 
 int /*<<< orphan*/  VP8EncFreeBitWriters (TYPE_1__* const) ; 
 int /*<<< orphan*/  VP8_ENC_ERROR_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  WebPEncodingSetError (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* kAverageBytesPerMB ; 

__attribute__((used)) static int PreLoopInitialize(VP8Encoder* const enc) {
  int p;
  int ok = 1;
  const int average_bytes_per_MB = kAverageBytesPerMB[enc->base_quant_ >> 4];
  const int bytes_per_parts =
      enc->mb_w_ * enc->mb_h_ * average_bytes_per_MB / enc->num_parts_;
  // Initialize the bit-writers
  for (p = 0; ok && p < enc->num_parts_; ++p) {
    ok = VP8BitWriterInit(enc->parts_ + p, bytes_per_parts);
  }
  if (!ok) {
    VP8EncFreeBitWriters(enc);  // malloc error occurred
    WebPEncodingSetError(enc->pic_, VP8_ENC_ERROR_OUT_OF_MEMORY);
  }
  return ok;
}