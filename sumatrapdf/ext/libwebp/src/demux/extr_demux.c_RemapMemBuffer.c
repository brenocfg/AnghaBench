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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {size_t buf_size_; size_t end_; int /*<<< orphan*/  const* buf_; } ;
typedef  TYPE_1__ MemBuffer ;

/* Variables and functions */

__attribute__((used)) static int RemapMemBuffer(MemBuffer* const mem,
                          const uint8_t* data, size_t size) {
  if (size < mem->buf_size_) return 0;  // can't remap to a shorter buffer!

  mem->buf_ = data;
  mem->end_ = mem->buf_size_ = size;
  return 1;
}