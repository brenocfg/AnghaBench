#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int nRight; int /*<<< orphan*/ * aRhs; int /*<<< orphan*/  lhs; } ;
typedef  int /*<<< orphan*/  Segment ;
typedef  int /*<<< orphan*/  LsmPgno ;
typedef  TYPE_1__ Level ;

/* Variables and functions */
 scalar_t__ fsRunEndsBetween (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsLevelEndsBetween(
  Level *pLevel, 
  Segment *pIgnore, 
  LsmPgno iFirst, 
  LsmPgno iLast
){
  int i;

  if( fsRunEndsBetween(&pLevel->lhs, pIgnore, iFirst, iLast) ){
    return 1;
  }
  for(i=0; i<pLevel->nRight; i++){
    if( fsRunEndsBetween(&pLevel->aRhs[i], pIgnore, iFirst, iLast) ){
      return 1;
    }
  }

  return 0;
}