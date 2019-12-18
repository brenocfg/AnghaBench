#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int iPos; int iColumn; int iOffset; TYPE_1__* dlw; } ;
struct TYPE_4__ {scalar_t__ iType; int /*<<< orphan*/  b; } ;
typedef  TYPE_2__ PLWriter ;

/* Variables and functions */
 scalar_t__ DL_DOCIDS ; 
 scalar_t__ DL_POSITIONS_OFFSETS ; 
 int POS_BASE ; 
 int POS_COLUMN ; 
 int VARINT_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dataBufferAppend (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ putVarint (char*,int) ; 

__attribute__((used)) static void plwAdd(PLWriter *pWriter, int iColumn, int iPos,
                   int iStartOffset, int iEndOffset){
  /* Worst-case space for POS_COLUMN, iColumn, iPosDelta,
  ** iStartOffsetDelta, and iEndOffsetDelta.
  */
  char c[5*VARINT_MAX];
  int n = 0;

  /* Ban plwAdd() after plwTerminate(). */
  assert( pWriter->iPos!=-1 );

  if( pWriter->dlw->iType==DL_DOCIDS ) return;

  if( iColumn!=pWriter->iColumn ){
    n += putVarint(c+n, POS_COLUMN);
    n += putVarint(c+n, iColumn);
    pWriter->iColumn = iColumn;
    pWriter->iPos = 0;
    pWriter->iOffset = 0;
  }
  assert( iPos>=pWriter->iPos );
  n += putVarint(c+n, POS_BASE+(iPos-pWriter->iPos));
  pWriter->iPos = iPos;
  if( pWriter->dlw->iType==DL_POSITIONS_OFFSETS ){
    assert( iStartOffset>=pWriter->iOffset );
    n += putVarint(c+n, iStartOffset-pWriter->iOffset);
    pWriter->iOffset = iStartOffset;
    assert( iEndOffset>=iStartOffset );
    n += putVarint(c+n, iEndOffset-iStartOffset);
  }
  dataBufferAppend(pWriter->dlw->b, c, n);
}