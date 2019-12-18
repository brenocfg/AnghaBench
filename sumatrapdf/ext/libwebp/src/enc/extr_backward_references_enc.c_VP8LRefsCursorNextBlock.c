#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* cur_block_; int /*<<< orphan*/ * last_pos_; int /*<<< orphan*/ * cur_pos; } ;
typedef  TYPE_1__ VP8LRefsCursor ;
struct TYPE_5__ {int size_; int /*<<< orphan*/ * start_; struct TYPE_5__* next_; } ;
typedef  TYPE_2__ PixOrCopyBlock ;

/* Variables and functions */

void VP8LRefsCursorNextBlock(VP8LRefsCursor* const c) {
  PixOrCopyBlock* const b = c->cur_block_->next_;
  c->cur_pos = (b == NULL) ? NULL : b->start_;
  c->last_pos_ = (b == NULL) ? NULL : b->start_ + b->size_;
  c->cur_block_ = b;
}