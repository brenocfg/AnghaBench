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
typedef  int UInt32 ;
struct TYPE_4__ {int range; int low; } ;
typedef  TYPE_1__ CRangeEnc ;

/* Variables and functions */
 int /*<<< orphan*/  RangeEnc_ShiftLow (TYPE_1__*) ; 
 int kTopValue ; 

__attribute__((used)) static void RangeEnc_EncodeDirectBits(CRangeEnc *p, UInt32 value, int numBits)
{
  do
  {
    p->range >>= 1;
    p->low += p->range & (0 - ((value >> --numBits) & 1));
    if (p->range < kTopValue)
    {
      p->range <<= 8;
      RangeEnc_ShiftLow(p);
    }
  }
  while (numBits != 0);
}