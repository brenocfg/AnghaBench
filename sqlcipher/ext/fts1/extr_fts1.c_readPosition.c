#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int iLastPos; int iLastColumn; int /*<<< orphan*/  p; TYPE_1__* pDoclist; } ;
struct TYPE_5__ {int iType; } ;
typedef  TYPE_2__ DocListReader ;

/* Variables and functions */
 int DL_POSITIONS ; 
 int DL_POSITIONS_OFFSETS ; 
 int POS_BASE ; 
 int POS_COLUMN ; 
 int POS_END ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  atEnd (TYPE_2__*) ; 
 scalar_t__ getVarint32 (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int readPosition(DocListReader *pReader, int *iColumn){
  int i;
  int iType = pReader->pDoclist->iType;

  if( pReader->iLastPos==-1 ){
    return -1;
  }
  assert( !atEnd(pReader) );

  if( iType<DL_POSITIONS ){
    return -1;
  }
  pReader->p += getVarint32(pReader->p, &i);
  if( i==POS_END ){
    pReader->iLastColumn = pReader->iLastPos = -1;
    *iColumn = -1;
    return -1;
  }
  if( i==POS_COLUMN ){
    pReader->p += getVarint32(pReader->p, &pReader->iLastColumn);
    pReader->iLastPos = 0;
    pReader->p += getVarint32(pReader->p, &i);
    assert( i>=POS_BASE );
  }
  pReader->iLastPos += ((int) i)-POS_BASE;
  if( iType>=DL_POSITIONS_OFFSETS ){
    /* Skip over offsets, ignoring them for now. */
    int iStart, iEnd;
    pReader->p += getVarint32(pReader->p, &iStart);
    pReader->p += getVarint32(pReader->p, &iEnd);
  }
  *iColumn = pReader->iLastColumn;
  return pReader->iLastPos;
}