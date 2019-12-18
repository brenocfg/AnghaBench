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
struct TYPE_5__ {size_t cur_; size_t buf_; scalar_t__ end_; int /*<<< orphan*/  error_; int /*<<< orphan*/  used_; int /*<<< orphan*/  bits_; } ;
typedef  TYPE_1__ VP8LBitWriter ;

/* Variables and functions */
 int /*<<< orphan*/  VP8LBitWriterResize (TYPE_1__* const,size_t const) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,size_t const) ; 

int VP8LBitWriterClone(const VP8LBitWriter* const src,
                       VP8LBitWriter* const dst) {
  const size_t current_size = src->cur_ - src->buf_;
  assert(src->cur_ >= src->buf_ && src->cur_ <= src->end_);
  if (!VP8LBitWriterResize(dst, current_size)) return 0;
  memcpy(dst->buf_, src->buf_, current_size);
  dst->bits_ = src->bits_;
  dst->used_ = src->used_;
  dst->error_ = src->error_;
  dst->cur_ = dst->buf_ + current_size;
  return 1;
}