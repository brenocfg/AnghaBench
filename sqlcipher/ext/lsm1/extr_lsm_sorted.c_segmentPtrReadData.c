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
struct TYPE_3__ {int /*<<< orphan*/  pPg; int /*<<< orphan*/  pSeg; } ;
typedef  TYPE_1__ SegmentPtr ;
typedef  int /*<<< orphan*/  LsmBlob ;

/* Variables and functions */
 int sortedReadData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,void**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int segmentPtrReadData(
  SegmentPtr *pPtr,
  int iOff,
  int nByte,
  void **ppData,
  LsmBlob *pBlob
){
  return sortedReadData(pPtr->pSeg, pPtr->pPg, iOff, nByte, ppData, pBlob);
}