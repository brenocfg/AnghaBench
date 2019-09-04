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
struct TYPE_3__ {int size; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ ZSTD_outBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  FUZZ_ASSERT (int) ; 
 int FUZZ_rand (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buf ; 
 int kBufSize ; 
 int /*<<< orphan*/  seed ; 

__attribute__((used)) static ZSTD_outBuffer makeOutBuffer(void)
{
  ZSTD_outBuffer buffer = { buf, 0, 0 };

  buffer.size = (FUZZ_rand(&seed) % kBufSize) + 1;
  FUZZ_ASSERT(buffer.size <= kBufSize);

  return buffer;
}