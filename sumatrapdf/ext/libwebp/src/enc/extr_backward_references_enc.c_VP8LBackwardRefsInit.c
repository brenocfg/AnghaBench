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
struct TYPE_4__ {int block_size_; int /*<<< orphan*/  refs_; int /*<<< orphan*/ * tail_; } ;
typedef  TYPE_1__ VP8LBackwardRefs ;

/* Variables and functions */
 int MIN_BLOCK_SIZE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__* const,int /*<<< orphan*/ ,int) ; 

void VP8LBackwardRefsInit(VP8LBackwardRefs* const refs, int block_size) {
  assert(refs != NULL);
  memset(refs, 0, sizeof(*refs));
  refs->tail_ = &refs->refs_;
  refs->block_size_ =
      (block_size < MIN_BLOCK_SIZE) ? MIN_BLOCK_SIZE : block_size;
}