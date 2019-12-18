#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  token_t ;
struct TYPE_5__ {struct TYPE_5__* next_; } ;
typedef  TYPE_1__ VP8Tokens ;
struct TYPE_6__ {int error_; int page_size_; int left_; int /*<<< orphan*/ * tokens_; TYPE_1__** last_page_; } ;
typedef  TYPE_2__ VP8TBuffer ;

/* Variables and functions */
 scalar_t__ TOKEN_DATA (TYPE_1__*) ; 
 scalar_t__ WebPSafeMalloc (unsigned long long,size_t const) ; 

__attribute__((used)) static int TBufferNewPage(VP8TBuffer* const b) {
  VP8Tokens* page = NULL;
  if (!b->error_) {
    const size_t size = sizeof(*page) + b->page_size_ * sizeof(token_t);
    page = (VP8Tokens*)WebPSafeMalloc(1ULL, size);
  }
  if (page == NULL) {
    b->error_ = 1;
    return 0;
  }
  page->next_ = NULL;

  *b->last_page_ = page;
  b->last_page_ = &page->next_;
  b->left_ = b->page_size_;
  b->tokens_ = (token_t*)TOKEN_DATA(page);
  return 1;
}