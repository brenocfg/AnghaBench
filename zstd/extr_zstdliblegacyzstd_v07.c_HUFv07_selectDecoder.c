#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t U32 ;
struct TYPE_2__ {size_t tableTime; size_t const decode256Time; } ;

/* Variables and functions */
 TYPE_1__** algoTime ; 

U32 HUFv07_selectDecoder (size_t dstSize, size_t cSrcSize)
{
    /* decoder timing evaluation */
    U32 const Q = (U32)(cSrcSize * 16 / dstSize);   /* Q < 16 since dstSize > cSrcSize */
    U32 const D256 = (U32)(dstSize >> 8);
    U32 const DTime0 = algoTime[Q][0].tableTime + (algoTime[Q][0].decode256Time * D256);
    U32 DTime1 = algoTime[Q][1].tableTime + (algoTime[Q][1].decode256Time * D256);
    DTime1 += DTime1 >> 3;  /* advantage to algorithm using less memory, for cache eviction */

    return DTime1 < DTime0;
}