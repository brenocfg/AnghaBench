#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* pConfig; } ;
struct TYPE_7__ {int flags; int /*<<< orphan*/  xNext; } ;
struct TYPE_6__ {scalar_t__ eDetail; } ;
typedef  TYPE_2__ Fts5SegIter ;
typedef  TYPE_3__ Fts5Index ;

/* Variables and functions */
 scalar_t__ FTS5_DETAIL_NONE ; 
 int FTS5_SEGITER_REVERSE ; 
 int /*<<< orphan*/  fts5SegIterNext ; 
 int /*<<< orphan*/  fts5SegIterNext_None ; 
 int /*<<< orphan*/  fts5SegIterNext_Reverse ; 

__attribute__((used)) static void fts5SegIterSetNext(Fts5Index *p, Fts5SegIter *pIter){
  if( pIter->flags & FTS5_SEGITER_REVERSE ){
    pIter->xNext = fts5SegIterNext_Reverse;
  }else if( p->pConfig->eDetail==FTS5_DETAIL_NONE ){
    pIter->xNext = fts5SegIterNext_None;
  }else{
    pIter->xNext = fts5SegIterNext;
  }
}