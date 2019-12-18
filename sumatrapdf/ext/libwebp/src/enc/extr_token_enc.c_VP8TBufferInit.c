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
struct TYPE_3__ {int page_size_; scalar_t__ error_; scalar_t__ left_; int /*<<< orphan*/ * pages_; int /*<<< orphan*/ ** last_page_; int /*<<< orphan*/ * tokens_; } ;
typedef  TYPE_1__ VP8TBuffer ;

/* Variables and functions */
 int MIN_PAGE_SIZE ; 

void VP8TBufferInit(VP8TBuffer* const b, int page_size) {
  b->tokens_ = NULL;
  b->pages_ = NULL;
  b->last_page_ = &b->pages_;
  b->left_ = 0;
  b->page_size_ = (page_size < MIN_PAGE_SIZE) ? MIN_PAGE_SIZE : page_size;
  b->error_ = 0;
}