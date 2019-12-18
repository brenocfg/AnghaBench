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
typedef  int bit_t ;
struct TYPE_3__ {int value_; int eof_; scalar_t__ bits_; int /*<<< orphan*/ * buf_; int /*<<< orphan*/ * buf_end_; } ;
typedef  TYPE_1__ VP8BitReader ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void VP8LoadFinalBytes(VP8BitReader* const br) {
  assert(br != NULL && br->buf_ != NULL);
  // Only read 8bits at a time
  if (br->buf_ < br->buf_end_) {
    br->bits_ += 8;
    br->value_ = (bit_t)(*br->buf_++) | (br->value_ << 8);
  } else if (!br->eof_) {
    br->value_ <<= 8;
    br->bits_ += 8;
    br->eof_ = 1;
  } else {
    br->bits_ = 0;  // This is to avoid undefined behaviour with shifts.
  }
}