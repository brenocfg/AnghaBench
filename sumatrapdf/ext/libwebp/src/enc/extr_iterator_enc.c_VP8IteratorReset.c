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
struct TYPE_7__ {int mb_w_; int mb_h_; } ;
typedef  TYPE_1__ VP8Encoder ;
struct TYPE_8__ {scalar_t__ do_trellis_; int /*<<< orphan*/  bit_count_; TYPE_1__* enc_; } ;
typedef  TYPE_2__ VP8EncIterator ;

/* Variables and functions */
 int /*<<< orphan*/  InitTop (TYPE_2__* const) ; 
 int /*<<< orphan*/  VP8IteratorSetCountDown (TYPE_2__* const,int) ; 
 int /*<<< orphan*/  VP8IteratorSetRow (TYPE_2__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void VP8IteratorReset(VP8EncIterator* const it) {
  VP8Encoder* const enc = it->enc_;
  VP8IteratorSetRow(it, 0);
  VP8IteratorSetCountDown(it, enc->mb_w_ * enc->mb_h_);  // default
  InitTop(it);
  memset(it->bit_count_, 0, sizeof(it->bit_count_));
  it->do_trellis_ = 0;
}