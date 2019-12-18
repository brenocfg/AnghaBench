#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  pIdxIter; int /*<<< orphan*/  pTblIter; } ;
typedef  TYPE_1__ RbuObjIter ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rbuObjIterClearStatements (TYPE_1__*) ; 
 int /*<<< orphan*/  rbuObjIterFreeCols (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rbuObjIterFinalize(RbuObjIter *pIter){
  rbuObjIterClearStatements(pIter);
  sqlite3_finalize(pIter->pTblIter);
  sqlite3_finalize(pIter->pIdxIter);
  rbuObjIterFreeCols(pIter);
  memset(pIter, 0, sizeof(RbuObjIter));
}