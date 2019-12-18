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
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_4__ {int iAuxOp; int iAuxArg; struct TYPE_4__* pNextAux; int /*<<< orphan*/  pAux; int /*<<< orphan*/  (* xDeleteAux ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ AuxData ;

/* Variables and functions */
 int MASKBIT32 (int) ; 
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testcase (int) ; 

void sqlite3VdbeDeleteAuxData(sqlite3 *db, AuxData **pp, int iOp, int mask){
  while( *pp ){
    AuxData *pAux = *pp;
    if( (iOp<0)
     || (pAux->iAuxOp==iOp
          && pAux->iAuxArg>=0
          && (pAux->iAuxArg>31 || !(mask & MASKBIT32(pAux->iAuxArg))))
    ){
      testcase( pAux->iAuxArg==31 );
      if( pAux->xDeleteAux ){
        pAux->xDeleteAux(pAux->pAux);
      }
      *pp = pAux->pNextAux;
      sqlite3DbFree(db, pAux);
    }else{
      pp= &pAux->pNextAux;
    }
  }
}