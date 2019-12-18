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
typedef  int vp8l_val_t ;
struct TYPE_4__ {int bit_pos_; scalar_t__ pos_; scalar_t__ len_; int val_; scalar_t__ buf_; } ;
typedef  TYPE_1__ VP8LBitReader ;

/* Variables and functions */
 scalar_t__ HToLE32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShiftBytes (TYPE_1__* const) ; 
 int VP8L_LBITS ; 
 scalar_t__ VP8L_LOG8_WBITS ; 
 int VP8L_WBITS ; 
 int /*<<< orphan*/  WebPMemToUint32 (scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 

void VP8LDoFillBitWindow(VP8LBitReader* const br) {
  assert(br->bit_pos_ >= VP8L_WBITS);
#if defined(VP8L_USE_FAST_LOAD)
  if (br->pos_ + sizeof(br->val_) < br->len_) {
    br->val_ >>= VP8L_WBITS;
    br->bit_pos_ -= VP8L_WBITS;
    br->val_ |= (vp8l_val_t)HToLE32(WebPMemToUint32(br->buf_ + br->pos_)) <<
                (VP8L_LBITS - VP8L_WBITS);
    br->pos_ += VP8L_LOG8_WBITS;
    return;
  }
#endif
  ShiftBytes(br);       // Slow path.
}