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
 scalar_t__ DL_POSITIONS_OFFSETS ; 
 int /*<<< orphan*/  appendVarint (TYPE_1__*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  docListAddPos (TYPE_1__*,int) ; 

__attribute__((used)) static void docListAddPosOffset(DocList *d, int iPos,
                                int iStartOffset, int iEndOffset){
  assert( d->iType==DL_POSITIONS_OFFSETS );
  docListAddPos(d, iPos);
  appendVarint(d, iStartOffset-d->iLastOffset);
  d->iLastOffset = iStartOffset;
  appendVarint(d, iEndOffset-iStartOffset);
}