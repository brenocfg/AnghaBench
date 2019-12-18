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
typedef  int /*<<< orphan*/  TestDb ;
struct TYPE_6__ {TYPE_1__** apFile; int /*<<< orphan*/  aBuffer; int /*<<< orphan*/  pBt; } ;
struct TYPE_5__ {scalar_t__ pBt; } ;
typedef  TYPE_2__ BtDb ;

/* Variables and functions */
 int /*<<< orphan*/  bgc_detach (TYPE_2__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int sqlite4BtClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testFree (TYPE_2__*) ; 

__attribute__((used)) static int bt_close(TestDb *pTestDb){
  BtDb *p = (BtDb*)pTestDb;
  int rc = sqlite4BtClose(p->pBt);
  free(p->aBuffer);
  if( p->apFile[0] ) p->apFile[0]->pBt = 0;
  if( p->apFile[1] ) p->apFile[1]->pBt = 0;
  bgc_detach(p);
  testFree(p);
  return rc;
}