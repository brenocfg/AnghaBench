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
struct TYPE_6__ {TYPE_2__* free_blocks_; } ;
typedef  TYPE_1__ VP8LBackwardRefs ;
struct TYPE_7__ {struct TYPE_7__* next_; } ;
typedef  TYPE_2__ PixOrCopyBlock ;

/* Variables and functions */
 int /*<<< orphan*/  VP8LClearBackwardRefs (TYPE_1__* const) ; 
 int /*<<< orphan*/  WebPSafeFree (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void VP8LBackwardRefsClear(VP8LBackwardRefs* const refs) {
  assert(refs != NULL);
  VP8LClearBackwardRefs(refs);
  while (refs->free_blocks_ != NULL) {
    PixOrCopyBlock* const next = refs->free_blocks_->next_;
    WebPSafeFree(refs->free_blocks_);
    refs->free_blocks_ = next;
  }
}