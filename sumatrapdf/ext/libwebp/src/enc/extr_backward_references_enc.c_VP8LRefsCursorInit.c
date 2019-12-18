#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * last_pos_; int /*<<< orphan*/ * cur_pos; TYPE_1__* cur_block_; } ;
typedef  TYPE_2__ VP8LRefsCursor ;
struct TYPE_8__ {TYPE_1__* refs_; } ;
typedef  TYPE_3__ VP8LBackwardRefs ;
struct TYPE_6__ {int size_; int /*<<< orphan*/ * start_; } ;

/* Variables and functions */

VP8LRefsCursor VP8LRefsCursorInit(const VP8LBackwardRefs* const refs) {
  VP8LRefsCursor c;
  c.cur_block_ = refs->refs_;
  if (refs->refs_ != NULL) {
    c.cur_pos = c.cur_block_->start_;
    c.last_pos_ = c.cur_pos + c.cur_block_->size_;
  } else {
    c.cur_pos = NULL;
    c.last_pos_ = NULL;
  }
  return c;
}