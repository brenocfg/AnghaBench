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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/ * buf_; scalar_t__ nb_bits_; } ;
typedef  TYPE_1__ VP8BitWriter ;

/* Variables and functions */
 int /*<<< orphan*/  Flush (TYPE_1__* const) ; 
 int /*<<< orphan*/  VP8PutBits (TYPE_1__* const,int /*<<< orphan*/ ,scalar_t__) ; 

uint8_t* VP8BitWriterFinish(VP8BitWriter* const bw) {
  VP8PutBits(bw, 0, 9 - bw->nb_bits_);
  bw->nb_bits_ = 0;   // pad with zeroes
  Flush(bw);
  return bw->buf_;
}