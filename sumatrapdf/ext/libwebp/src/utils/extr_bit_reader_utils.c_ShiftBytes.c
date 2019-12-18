#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int vp8l_val_t ;
struct TYPE_5__ {int bit_pos_; size_t pos_; size_t len_; int val_; scalar_t__* buf_; } ;
typedef  TYPE_1__ VP8LBitReader ;

/* Variables and functions */
 scalar_t__ VP8LIsEndOfStream (TYPE_1__* const) ; 
 int /*<<< orphan*/  VP8LSetEndOfStream (TYPE_1__* const) ; 
 int VP8L_LBITS ; 

__attribute__((used)) static void ShiftBytes(VP8LBitReader* const br) {
  while (br->bit_pos_ >= 8 && br->pos_ < br->len_) {
    br->val_ >>= 8;
    br->val_ |= ((vp8l_val_t)br->buf_[br->pos_]) << (VP8L_LBITS - 8);
    ++br->pos_;
    br->bit_pos_ -= 8;
  }
  if (VP8LIsEndOfStream(br)) {
    VP8LSetEndOfStream(br);
  }
}