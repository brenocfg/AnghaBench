#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* pDb; } ;
struct TYPE_7__ {int /*<<< orphan*/  nKey; int /*<<< orphan*/  pKey; int /*<<< orphan*/  eType; scalar_t__ pPg; } ;
struct TYPE_6__ {int /*<<< orphan*/  xCmp; } ;
typedef  TYPE_2__ SegmentPtr ;
typedef  TYPE_3__ MultiCursor ;

/* Variables and functions */
 int LSM_SEEK_EQ ; 
 int LSM_SEEK_GE ; 
 int LSM_SEEK_LE ; 
 int /*<<< orphan*/  rtTopic (int /*<<< orphan*/ ) ; 
 int sortedKeyCompare (int /*<<< orphan*/ ,int,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int assertSeekResult(
  MultiCursor *pCsr,
  SegmentPtr *pPtr,
  int iTopic,
  void *pKey,
  int nKey,
  int eSeek
){
  if( pPtr->pPg ){
    int res;
    res = sortedKeyCompare(pCsr->pDb->xCmp, iTopic, pKey, nKey,
        rtTopic(pPtr->eType), pPtr->pKey, pPtr->nKey
    );

    if( eSeek==LSM_SEEK_EQ ) return (res==0);
    if( eSeek==LSM_SEEK_LE ) return (res>=0);
    if( eSeek==LSM_SEEK_GE ) return (res<=0);
  }

  return 1;
}