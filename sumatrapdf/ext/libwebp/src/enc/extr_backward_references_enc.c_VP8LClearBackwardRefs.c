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
struct TYPE_3__ {int /*<<< orphan*/ * refs_; int /*<<< orphan*/ * last_block_; int /*<<< orphan*/ ** tail_; int /*<<< orphan*/ * free_blocks_; } ;
typedef  TYPE_1__ VP8LBackwardRefs ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void VP8LClearBackwardRefs(VP8LBackwardRefs* const refs) {
  assert(refs != NULL);
  if (refs->tail_ != NULL) {
    *refs->tail_ = refs->free_blocks_;  // recycle all blocks at once
  }
  refs->free_blocks_ = refs->refs_;
  refs->tail_ = &refs->refs_;
  refs->last_block_ = NULL;
  refs->refs_ = NULL;
}