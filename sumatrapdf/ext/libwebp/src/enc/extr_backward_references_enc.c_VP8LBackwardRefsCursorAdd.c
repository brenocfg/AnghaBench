#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ block_size_; TYPE_2__* last_block_; } ;
typedef  TYPE_1__ VP8LBackwardRefs ;
struct TYPE_7__ {scalar_t__ size_; int /*<<< orphan*/ * start_; } ;
typedef  TYPE_2__ PixOrCopyBlock ;
typedef  int /*<<< orphan*/  PixOrCopy ;

/* Variables and functions */
 TYPE_2__* BackwardRefsNewBlock (TYPE_1__* const) ; 

void VP8LBackwardRefsCursorAdd(VP8LBackwardRefs* const refs,
                               const PixOrCopy v) {
  PixOrCopyBlock* b = refs->last_block_;
  if (b == NULL || b->size_ == refs->block_size_) {
    b = BackwardRefsNewBlock(refs);
    if (b == NULL) return;   // refs->error_ is set
  }
  b->start_[b->size_++] = v;
}