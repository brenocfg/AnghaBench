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
struct TYPE_4__ {scalar_t__ iType; } ;
typedef  int /*<<< orphan*/  PLWriter ;
typedef  int /*<<< orphan*/  PLReader ;
typedef  TYPE_1__ DLWriter ;
typedef  int /*<<< orphan*/  DLReader ;

/* Variables and functions */
 scalar_t__ DL_POSITIONS_OFFSETS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ dlrDocid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plrAtEnd (int /*<<< orphan*/ *) ; 
 scalar_t__ plrColumn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plrDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plrInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ plrPosition (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plrStep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plwAdd (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plwDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plwInit (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  plwTerminate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void posListPhraseMerge(DLReader *pLeft, DLReader *pRight,
                               DLWriter *pOut){
  PLReader left, right;
  PLWriter writer;
  int match = 0;

  assert( dlrDocid(pLeft)==dlrDocid(pRight) );
  assert( pOut->iType!=DL_POSITIONS_OFFSETS );

  plrInit(&left, pLeft);
  plrInit(&right, pRight);

  while( !plrAtEnd(&left) && !plrAtEnd(&right) ){
    if( plrColumn(&left)<plrColumn(&right) ){
      plrStep(&left);
    }else if( plrColumn(&left)>plrColumn(&right) ){
      plrStep(&right);
    }else if( plrPosition(&left)+1<plrPosition(&right) ){
      plrStep(&left);
    }else if( plrPosition(&left)+1>plrPosition(&right) ){
      plrStep(&right);
    }else{
      if( !match ){
        plwInit(&writer, pOut, dlrDocid(pLeft));
        match = 1;
      }
      plwAdd(&writer, plrColumn(&right), plrPosition(&right), 0, 0);
      plrStep(&left);
      plrStep(&right);
    }
  }

  if( match ){
    plwTerminate(&writer);
    plwDestroy(&writer);
  }

  plrDestroy(&left);
  plrDestroy(&right);
}