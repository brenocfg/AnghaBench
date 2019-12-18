#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  const uint32_t ;
struct TYPE_5__ {int start_; int /*<<< orphan*/ * buf_; } ;
typedef  TYPE_1__ MemBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  const GetLE32 (int /*<<< orphan*/  const* const) ; 
 int MemDataSize (TYPE_1__* const) ; 
 int /*<<< orphan*/  Skip (TYPE_1__* const,int) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static uint32_t ReadMemBufLE32(MemBuffer* const mem) {
  const uint8_t* const data = mem->buf_ + mem->start_;
  const uint32_t val = GetLE32(data);
  assert(MemDataSize(mem) >= 4);
  Skip(mem, 4);
  return val;
}