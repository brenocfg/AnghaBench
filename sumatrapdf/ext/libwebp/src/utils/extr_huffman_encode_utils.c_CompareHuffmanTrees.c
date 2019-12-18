#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ total_count_; scalar_t__ value_; } ;
typedef  TYPE_1__ HuffmanTree ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int CompareHuffmanTrees(const void* ptr1, const void* ptr2) {
  const HuffmanTree* const t1 = (const HuffmanTree*)ptr1;
  const HuffmanTree* const t2 = (const HuffmanTree*)ptr2;
  if (t1->total_count_ > t2->total_count_) {
    return -1;
  } else if (t1->total_count_ < t2->total_count_) {
    return 1;
  } else {
    assert(t1->value_ != t2->value_);
    return (t1->value_ < t2->value_) ? -1 : 1;
  }
}