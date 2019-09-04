#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sNC ;
struct TYPE_15__ {int /*<<< orphan*/  pParse; } ;
typedef  TYPE_3__ Walker ;
struct TYPE_17__ {int /*<<< orphan*/  pParse; } ;
struct TYPE_16__ {TYPE_1__* pWith; } ;
struct TYPE_14__ {TYPE_4__* pSelect; } ;
struct TYPE_13__ {int nCte; TYPE_2__* a; } ;
typedef  TYPE_4__ Select ;
typedef  TYPE_5__ NameContext ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3SelectPrep (int /*<<< orphan*/ ,TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  sqlite3WalkSelect (TYPE_3__*,TYPE_4__*) ; 

__attribute__((used)) static void renameWalkWith(Walker *pWalker, Select *pSelect){
  if( pSelect->pWith ){
    int i;
    for(i=0; i<pSelect->pWith->nCte; i++){
      Select *p = pSelect->pWith->a[i].pSelect;
      NameContext sNC;
      memset(&sNC, 0, sizeof(sNC));
      sNC.pParse = pWalker->pParse;
      sqlite3SelectPrep(sNC.pParse, p, &sNC);
      sqlite3WalkSelect(pWalker, p);
    }
  }
}