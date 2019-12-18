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
struct TYPE_5__ {scalar_t__ iType; int iLastOffset; } ;
typedef  TYPE_1__ DocList ;

/* Variables and functions */
 scalar_t__ DL_POSITIONS ; 
 scalar_t__ DL_POSITIONS_OFFSETS ; 
 int POS_END ; 
 int /*<<< orphan*/  addPos (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  appendVarint (TYPE_1__*,int) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void docListAddPosOffset(
  DocList *d,             /* Doclist under construction */
  int iColumn,            /* Column the inserted term is part of */
  int iPos,               /* Position of the inserted term */
  int iStartOffset,       /* Starting offset of inserted term */
  int iEndOffset          /* Ending offset of inserted term */
){
  assert( d->iType>=DL_POSITIONS );
  addPos(d, iColumn, iPos);
  if( d->iType==DL_POSITIONS_OFFSETS ){
    assert( iStartOffset>=d->iLastOffset );
    appendVarint(d, iStartOffset-d->iLastOffset);
    d->iLastOffset = iStartOffset;
    assert( iEndOffset>=iStartOffset );
    appendVarint(d, iEndOffset-iStartOffset);
  }
  appendVarint(d, POS_END);  /* add new terminator */
}