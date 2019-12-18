#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pEnv; } ;
typedef  TYPE_1__ lsm_db ;
struct TYPE_6__ {int n; scalar_t__ a; } ;
typedef  TYPE_2__ TreeBlob ;

/* Variables and functions */
 int /*<<< orphan*/  lsmFree (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ lsmMallocRc (int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int tblobGrow(lsm_db *pDb, TreeBlob *p, int n, int *pRc){
  if( n>p->n ){
    lsmFree(pDb->pEnv, p->a);
    p->a = lsmMallocRc(pDb->pEnv, n, pRc);
    p->n = n;
  }
  return (p->a==0);
}