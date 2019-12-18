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
struct TYPE_3__ {int /*<<< orphan*/  pBt; } ;
typedef  TYPE_1__ BtDb ;

/* Variables and functions */
 int SQLITE4_OK ; 
 int sqlite4BtBegin (int /*<<< orphan*/ ,int) ; 
 int sqlite4BtTransactionLevel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btMinTransaction(BtDb *p, int iMin, int *piLevel){
  int iLevel;
  int rc = SQLITE4_OK;

  iLevel = sqlite4BtTransactionLevel(p->pBt);
  if( iLevel<iMin ){ 
    rc = sqlite4BtBegin(p->pBt, iMin); 
    *piLevel = iLevel;
  }else{
    *piLevel = -1;
  }

  return rc;
}