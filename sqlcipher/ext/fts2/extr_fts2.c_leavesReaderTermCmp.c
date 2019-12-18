#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  leafReader; } ;
typedef  TYPE_1__ LeavesReader ;

/* Variables and functions */
 int leafReaderTermCmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ leavesReaderAtEnd (TYPE_1__*) ; 
 int /*<<< orphan*/  leavesReaderTerm (TYPE_1__*) ; 
 int /*<<< orphan*/  leavesReaderTermBytes (TYPE_1__*) ; 

__attribute__((used)) static int leavesReaderTermCmp(LeavesReader *lr1, LeavesReader *lr2){
  if( leavesReaderAtEnd(lr1) ){
    if( leavesReaderAtEnd(lr2) ) return 0;
    return 1;
  }
  if( leavesReaderAtEnd(lr2) ) return -1;

  return leafReaderTermCmp(&lr1->leafReader,
                           leavesReaderTerm(lr2), leavesReaderTermBytes(lr2),
                           0);
}