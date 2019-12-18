#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t UInt32 ;
typedef  size_t CLzRef ;

/* Variables and functions */
 size_t kEmptyHashValue ; 

void MatchFinder_Normalize3(UInt32 subValue, CLzRef *items, UInt32 numItems)
{
  UInt32 i;
  for (i = 0; i < numItems; i++)
  {
    UInt32 value = items[i];
    if (value <= subValue)
      value = kEmptyHashValue;
    else
      value -= subValue;
    items[i] = value;
  }
}