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
struct TYPE_4__ {int nData; int iColumn; int iPosition; scalar_t__ iType; int /*<<< orphan*/ * pData; scalar_t__ iStartOffset; scalar_t__ iEndOffset; } ;
typedef  TYPE_1__ PLReader ;

/* Variables and functions */
 scalar_t__ DL_POSITIONS_OFFSETS ; 
 int POS_BASE ; 
 int POS_COLUMN ; 
 int POS_END ; 
 int /*<<< orphan*/  assert (int) ; 
 int getVarint32 (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  plrAtEnd (TYPE_1__*) ; 

__attribute__((used)) static void plrStep(PLReader *pReader){
  int i, n;

  assert( !plrAtEnd(pReader) );

  if( pReader->nData==0 ){
    pReader->pData = NULL;
    return;
  }

  n = getVarint32(pReader->pData, &i);
  if( i==POS_COLUMN ){
    n += getVarint32(pReader->pData+n, &pReader->iColumn);
    pReader->iPosition = 0;
    pReader->iStartOffset = 0;
    n += getVarint32(pReader->pData+n, &i);
  }
  /* Should never see adjacent column changes. */
  assert( i!=POS_COLUMN );

  if( i==POS_END ){
    pReader->nData = 0;
    pReader->pData = NULL;
    return;
  }

  pReader->iPosition += i-POS_BASE;
  if( pReader->iType==DL_POSITIONS_OFFSETS ){
    n += getVarint32(pReader->pData+n, &i);
    pReader->iStartOffset += i;
    n += getVarint32(pReader->pData+n, &i);
    pReader->iEndOffset = pReader->iStartOffset+i;
  }
  assert( n<=pReader->nData );
  pReader->pData += n;
  pReader->nData -= n;
}