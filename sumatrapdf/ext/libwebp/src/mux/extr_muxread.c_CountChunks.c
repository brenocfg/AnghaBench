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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {scalar_t__ tag_; struct TYPE_3__* next_; } ;
typedef  TYPE_1__ WebPChunk ;

/* Variables and functions */
 scalar_t__ NIL_TAG ; 

__attribute__((used)) static int CountChunks(const WebPChunk* const chunk_list, uint32_t tag) {
  int count = 0;
  const WebPChunk* current;
  for (current = chunk_list; current != NULL; current = current->next_) {
    if (tag == NIL_TAG || current->tag_ == tag) {
      count++;  // Count chunks whose tags match.
    }
  }
  return count;
}