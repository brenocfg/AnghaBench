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
typedef  int stb_uint16 ;
typedef  int stb_uint ;
struct TYPE_3__ {int multiplicand; int b_mask; int table_mask; } ;
typedef  TYPE_1__ stb_perfect ;

/* Variables and functions */

__attribute__((used)) static void stb__perfect_prehash(stb_perfect *p, stb_uint x, stb_uint16 *a, stb_uint16 *b)
{
   stb_uint m = x * p->multiplicand;
   stb_uint y = x >> 16;
   stb_uint bv = (m >> 24) + y;
   stb_uint av = (m + y) >> 12;
   bv &= p->b_mask;
   av &= p->table_mask;
   *b = bv;
   *a = av;
}