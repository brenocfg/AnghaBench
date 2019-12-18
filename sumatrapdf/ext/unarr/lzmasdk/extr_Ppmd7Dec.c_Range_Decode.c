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
typedef  int UInt32 ;
struct TYPE_3__ {int Code; int Range; } ;
typedef  TYPE_1__ CPpmd7z_RangeDec ;

/* Variables and functions */
 int /*<<< orphan*/  Range_Normalize (TYPE_1__*) ; 

__attribute__((used)) static void Range_Decode(void *pp, UInt32 start, UInt32 size)
{
  CPpmd7z_RangeDec *p = (CPpmd7z_RangeDec *)pp;
  p->Code -= start * p->Range;
  p->Range *= size;
  Range_Normalize(p);
}