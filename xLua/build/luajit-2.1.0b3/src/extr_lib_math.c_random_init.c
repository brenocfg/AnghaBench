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
typedef  int uint32_t ;
struct TYPE_5__ {double d; int u64; } ;
typedef  TYPE_1__ U64double ;
struct TYPE_6__ {int* gen; int valid; } ;
typedef  TYPE_2__ RandomState ;

/* Variables and functions */
 int /*<<< orphan*/  lj_math_random_step (TYPE_2__*) ; 

__attribute__((used)) static void random_init(RandomState *rs, double d)
{
  uint32_t r = 0x11090601;  /* 64-k[i] as four 8 bit constants. */
  int i;
  for (i = 0; i < 4; i++) {
    U64double u;
    uint32_t m = 1u << (r&255);
    r >>= 8;
    u.d = d = d * 3.14159265358979323846 + 2.7182818284590452354;
    if (u.u64 < m) u.u64 += m;  /* Ensure k[i] MSB of gen[i] are non-zero. */
    rs->gen[i] = u.u64;
  }
  rs->valid = 1;
  for (i = 0; i < 10; i++)
    lj_math_random_step(rs);
}