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
struct TYPE_4__ {scalar_t__ nData; int iLastColumn; int iLastPos; int iLastOffset; } ;
typedef  TYPE_1__ DocList ;

/* Variables and functions */
 int POS_BASE ; 
 int POS_COLUMN ; 
 int /*<<< orphan*/  appendVarint (TYPE_1__*,int) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void addPos(DocList *d, int iColumn, int iPos){
  assert( d->nData>0 );
  --d->nData;  /* remove previous terminator */
  if( iColumn!=d->iLastColumn ){
    assert( iColumn>d->iLastColumn );
    appendVarint(d, POS_COLUMN);
    appendVarint(d, iColumn);
    d->iLastColumn = iColumn;
    d->iLastPos = d->iLastOffset = 0;
  }
  assert( iPos>=d->iLastPos );
  appendVarint(d, iPos-d->iLastPos+POS_BASE);
  d->iLastPos = iPos;
}