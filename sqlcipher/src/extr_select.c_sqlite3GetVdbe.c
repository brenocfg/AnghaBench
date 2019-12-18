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
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_4__ {scalar_t__ pToplevel; int okConstFactor; int /*<<< orphan*/  db; int /*<<< orphan*/ * pVdbe; } ;
typedef  TYPE_1__ Parse ;

/* Variables and functions */
 scalar_t__ OptimizationEnabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SQLITE_FactorOutConst ; 
 int /*<<< orphan*/ * sqlite3VdbeCreate (TYPE_1__*) ; 

Vdbe *sqlite3GetVdbe(Parse *pParse){
  if( pParse->pVdbe ){
    return pParse->pVdbe;
  }
  if( pParse->pToplevel==0
   && OptimizationEnabled(pParse->db,SQLITE_FactorOutConst)
  ){
    pParse->okConstFactor = 1;
  }
  return sqlite3VdbeCreate(pParse);
}