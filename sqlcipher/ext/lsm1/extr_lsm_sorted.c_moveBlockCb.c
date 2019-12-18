#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_2__ {int iFrom; int iSeen; } ;
typedef  TYPE_1__ MoveBlockCtx ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int moveBlockCb(void *pCtx, int iBlk, i64 iSnapshot){
  MoveBlockCtx *p = (MoveBlockCtx *)pCtx;
  assert( p->iFrom==0 );
  if( iBlk==(p->iSeen-1) ){
    p->iSeen = iBlk;
    return 0;
  }
  p->iFrom = p->iSeen-1;
  return 1;
}