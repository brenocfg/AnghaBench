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
struct TYPE_3__ {scalar_t__ priceType; int const litSumBasePrice; int /*<<< orphan*/ * litFreq; } ;
typedef  TYPE_1__ optState_t ;
typedef  int U32 ;
typedef  size_t BYTE ;

/* Variables and functions */
 int const BITCOST_MULTIPLIER ; 
 int WEIGHT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ zop_predef ; 

__attribute__((used)) static U32 ZSTD_rawLiteralsCost(const BYTE* const literals, U32 const litLength,
                                const optState_t* const optPtr,
                                int optLevel)
{
    if (litLength == 0) return 0;
    if (optPtr->priceType == zop_predef)
        return (litLength*6) * BITCOST_MULTIPLIER;  /* 6 bit per literal - no statistic used */

    /* dynamic statistics */
    {   U32 price = litLength * optPtr->litSumBasePrice;
        U32 u;
        for (u=0; u < litLength; u++) {
            assert(WEIGHT(optPtr->litFreq[literals[u]], optLevel) <= optPtr->litSumBasePrice);   /* literal cost should never be negative */
            price -= WEIGHT(optPtr->litFreq[literals[u]], optLevel);
        }
        return price;
    }
}