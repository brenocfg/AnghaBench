#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite_int64 ;
struct TYPE_5__ {scalar_t__ iType; } ;
typedef  int /*<<< orphan*/  DocListReader ;
typedef  TYPE_1__ DocList ;

/* Variables and functions */
 scalar_t__ DL_POSITIONS ; 
 int /*<<< orphan*/  docListAddDocid (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  docListAddPos (TYPE_1__*,int,int) ; 
 int readPosition (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  skipPositionList (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mergePosList(
  DocListReader *pLeft,    /* Left position list */
  DocListReader *pRight,   /* Right position list */
  sqlite_int64 iDocid,     /* The docid from pLeft and pRight */
  DocList *pOut            /* Write the merged document record here */
){
  int iLeftCol, iLeftPos = readPosition(pLeft, &iLeftCol);
  int iRightCol, iRightPos = readPosition(pRight, &iRightCol);
  int match = 0;

  /* Loop until we've reached the end of both position lists. */
  while( iLeftPos!=-1 && iRightPos!=-1 ){
    if( iLeftCol==iRightCol && iLeftPos+1==iRightPos ){
      if( !match ){
        docListAddDocid(pOut, iDocid);
        match = 1;
      }
      if( pOut->iType>=DL_POSITIONS ){
        docListAddPos(pOut, iRightCol, iRightPos);
      }
      iLeftPos = readPosition(pLeft, &iLeftCol);
      iRightPos = readPosition(pRight, &iRightCol);
    }else if( iRightCol<iLeftCol ||
              (iRightCol==iLeftCol && iRightPos<iLeftPos+1) ){
      iRightPos = readPosition(pRight, &iRightCol);
    }else{
      iLeftPos = readPosition(pLeft, &iLeftCol);
    }
  }
  if( iLeftPos>=0 ) skipPositionList(pLeft);
  if( iRightPos>=0 ) skipPositionList(pRight);
}