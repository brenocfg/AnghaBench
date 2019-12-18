#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ iType; } ;
struct TYPE_9__ {scalar_t__ iType; } ;
typedef  int /*<<< orphan*/  PLWriter ;
typedef  int /*<<< orphan*/  PLReader ;
typedef  TYPE_1__ DLWriter ;
typedef  TYPE_2__ DLReader ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ dlrDocid (TYPE_2__*) ; 
 int /*<<< orphan*/  plrAtEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plrDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plrInit (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  plrStep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plwCopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plwDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plwInit (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  plwTerminate (int /*<<< orphan*/ *) ; 
 int posListCmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void posListUnion(DLReader *pLeft, DLReader *pRight, DLWriter *pOut){
  PLReader left, right;
  PLWriter writer;

  assert( dlrDocid(pLeft)==dlrDocid(pRight) );
  assert( pLeft->iType==pRight->iType );
  assert( pLeft->iType==pOut->iType );

  plrInit(&left, pLeft);
  plrInit(&right, pRight);
  plwInit(&writer, pOut, dlrDocid(pLeft));

  while( !plrAtEnd(&left) || !plrAtEnd(&right) ){
    int c = posListCmp(&left, &right);
    if( c<0 ){
      plwCopy(&writer, &left);
      plrStep(&left);
    }else if( c>0 ){
      plwCopy(&writer, &right);
      plrStep(&right);
    }else{
      plwCopy(&writer, &left);
      plrStep(&left);
      plrStep(&right);
    }
  }

  plwTerminate(&writer);
  plwDestroy(&writer);
  plrDestroy(&left);
  plrDestroy(&right);
}