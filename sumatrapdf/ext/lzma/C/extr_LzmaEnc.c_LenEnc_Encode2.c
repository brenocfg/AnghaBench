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
typedef  size_t UInt32 ;
struct TYPE_4__ {scalar_t__* counters; int /*<<< orphan*/  p; } ;
typedef  int /*<<< orphan*/  CRangeEnc ;
typedef  TYPE_1__ CLenPriceEnc ;
typedef  scalar_t__ Bool ;

/* Variables and functions */
 int /*<<< orphan*/  LenEnc_Encode (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/  LenPriceEnc_UpdateTable (TYPE_1__*,size_t,size_t*) ; 

__attribute__((used)) static void LenEnc_Encode2(CLenPriceEnc *p, CRangeEnc *rc, UInt32 symbol, UInt32 posState, Bool updatePrice, UInt32 *ProbPrices)
{
  LenEnc_Encode(&p->p, rc, symbol, posState);
  if (updatePrice)
    if (--p->counters[posState] == 0)
      LenPriceEnc_UpdateTable(p, posState, ProbPrices);
}