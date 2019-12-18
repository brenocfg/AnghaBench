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
typedef  scalar_t__ vp8l_wtype_t ;
typedef  int vp8l_atype_t ;
typedef  size_t uint64_t ;
typedef  int const uint32_t ;
struct TYPE_4__ {int bits_; int used_; scalar_t__ cur_; scalar_t__ end_; size_t buf_; int error_; } ;
typedef  TYPE_1__ VP8LBitWriter ;

/* Variables and functions */
 size_t MIN_EXTRA_SIZE ; 
 int /*<<< orphan*/  VP8LBitWriterResize (TYPE_1__* const,size_t) ; 
 int VP8L_WRITER_BITS ; 
 scalar_t__ VP8L_WRITER_BYTES ; 
 int VP8L_WRITER_MAX_BITS ; 
 scalar_t__ WSWAP (scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 

void VP8LPutBitsInternal(VP8LBitWriter* const bw, uint32_t bits, int n_bits) {
  assert(n_bits <= 32);
  // That's the max we can handle:
  assert(sizeof(vp8l_wtype_t) == 2);
  if (n_bits > 0) {
    vp8l_atype_t lbits = bw->bits_;
    int used = bw->used_;
    // Special case of overflow handling for 32bit accumulator (2-steps flush).
#if VP8L_WRITER_BITS == 16
    if (used + n_bits >= VP8L_WRITER_MAX_BITS) {
      // Fill up all the VP8L_WRITER_MAX_BITS so it can be flushed out below.
      const int shift = VP8L_WRITER_MAX_BITS - used;
      lbits |= (vp8l_atype_t)bits << used;
      used = VP8L_WRITER_MAX_BITS;
      n_bits -= shift;
      bits >>= shift;
      assert(n_bits <= VP8L_WRITER_MAX_BITS);
    }
#endif
    // If needed, make some room by flushing some bits out.
    while (used >= VP8L_WRITER_BITS) {
      if (bw->cur_ + VP8L_WRITER_BYTES > bw->end_) {
        const uint64_t extra_size = (bw->end_ - bw->buf_) + MIN_EXTRA_SIZE;
        if (extra_size != (size_t)extra_size ||
            !VP8LBitWriterResize(bw, (size_t)extra_size)) {
          bw->cur_ = bw->buf_;
          bw->error_ = 1;
          return;
        }
      }
      *(vp8l_wtype_t*)bw->cur_ = (vp8l_wtype_t)WSWAP((vp8l_wtype_t)lbits);
      bw->cur_ += VP8L_WRITER_BYTES;
      lbits >>= VP8L_WRITER_BITS;
      used -= VP8L_WRITER_BITS;
    }
    bw->bits_ = lbits | ((vp8l_atype_t)bits << used);
    bw->used_ = used + n_bits;
  }
}