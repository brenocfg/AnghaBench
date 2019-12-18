#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ iType; } ;
typedef  TYPE_1__ PLReader ;

/* Variables and functions */
 scalar_t__ DL_DOCIDS ; 
 scalar_t__ DL_POSITIONS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ plrAtEnd (TYPE_1__*) ; 
 scalar_t__ plrColumn (TYPE_1__*) ; 
 scalar_t__ plrEndOffset (TYPE_1__*) ; 
 scalar_t__ plrPosition (TYPE_1__*) ; 
 scalar_t__ plrStartOffset (TYPE_1__*) ; 

__attribute__((used)) static int posListCmp(PLReader *pLeft, PLReader *pRight){
  assert( pLeft->iType==pRight->iType );
  if( pLeft->iType==DL_DOCIDS ) return 0;

  if( plrAtEnd(pLeft) ) return plrAtEnd(pRight) ? 0 : 1;
  if( plrAtEnd(pRight) ) return -1;

  if( plrColumn(pLeft)<plrColumn(pRight) ) return -1;
  if( plrColumn(pLeft)>plrColumn(pRight) ) return 1;

  if( plrPosition(pLeft)<plrPosition(pRight) ) return -1;
  if( plrPosition(pLeft)>plrPosition(pRight) ) return 1;
  if( pLeft->iType==DL_POSITIONS ) return 0;

  if( plrStartOffset(pLeft)<plrStartOffset(pRight) ) return -1;
  if( plrStartOffset(pLeft)>plrStartOffset(pRight) ) return 1;

  if( plrEndOffset(pLeft)<plrEndOffset(pRight) ) return -1;
  if( plrEndOffset(pLeft)>plrEndOffset(pRight) ) return 1;

  return 0;
}