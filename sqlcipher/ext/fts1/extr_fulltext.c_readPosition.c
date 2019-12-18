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
struct TYPE_6__ {int iLastPos; int /*<<< orphan*/  p; TYPE_1__* pDoclist; } ;
struct TYPE_5__ {int iType; } ;
typedef  TYPE_2__ DocListReader ;

/* Variables and functions */
 int DL_POSITIONS ; 
 int DL_POSITIONS_OFFSETS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ getVarint32 (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  readerAtEnd (TYPE_2__*) ; 

__attribute__((used)) static int readPosition(DocListReader *pReader){
  int i;
  int iType = pReader->pDoclist->iType;
  assert( iType>=DL_POSITIONS );
  assert( !readerAtEnd(pReader) );

  pReader->p += getVarint32(pReader->p, &i);
  if( i==0 ){
    pReader->iLastPos = -1;
    return -1;
  }
  pReader->iLastPos += ((int) i)-1;
  if( iType>=DL_POSITIONS_OFFSETS ){
    /* Skip over offsets, ignoring them for now. */
    int iStart, iEnd;
    pReader->p += getVarint32(pReader->p, &iStart);
    pReader->p += getVarint32(pReader->p, &iEnd);
  }
  return pReader->iLastPos;
}