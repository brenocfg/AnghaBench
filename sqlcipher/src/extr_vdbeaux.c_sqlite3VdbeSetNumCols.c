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
typedef  int u16 ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_3__ {int nResColumn; int /*<<< orphan*/ * aColName; int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ Vdbe ;
typedef  int /*<<< orphan*/  Mem ;

/* Variables and functions */
 int COLNAME_N ; 
 int /*<<< orphan*/  MEM_Null ; 
 int /*<<< orphan*/  initMemArray (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  releaseMemArray (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3DbMallocRawNN (int /*<<< orphan*/ *,int) ; 

void sqlite3VdbeSetNumCols(Vdbe *p, int nResColumn){
  int n;
  sqlite3 *db = p->db;

  if( p->nResColumn ){
    releaseMemArray(p->aColName, p->nResColumn*COLNAME_N);
    sqlite3DbFree(db, p->aColName);
  }
  n = nResColumn*COLNAME_N;
  p->nResColumn = (u16)nResColumn;
  p->aColName = (Mem*)sqlite3DbMallocRawNN(db, sizeof(Mem)*n );
  if( p->aColName==0 ) return;
  initMemArray(p->aColName, n, db, MEM_Null);
}