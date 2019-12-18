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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int iFirst; scalar_t__ iLastPg; int nSize; scalar_t__ iRoot; } ;
typedef  TYPE_1__ Segment ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 void* ckptGobble64 (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static void ckptNewSegment(
  u32 *aIn,
  int *piIn,
  Segment *pSegment               /* Populate this structure */
){
  assert( pSegment->iFirst==0 && pSegment->iLastPg==0 );
  assert( pSegment->nSize==0 && pSegment->iRoot==0 );
  pSegment->iFirst = ckptGobble64(aIn, piIn);
  pSegment->iLastPg = ckptGobble64(aIn, piIn);
  pSegment->iRoot = ckptGobble64(aIn, piIn);
  pSegment->nSize = (int)ckptGobble64(aIn, piIn);
  assert( pSegment->iFirst );
}