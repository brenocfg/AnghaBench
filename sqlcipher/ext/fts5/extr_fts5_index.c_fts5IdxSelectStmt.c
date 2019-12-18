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
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_6__ {int /*<<< orphan*/  zName; int /*<<< orphan*/  zDb; } ;
struct TYPE_5__ {scalar_t__ pIdxSelect; TYPE_2__* pConfig; } ;
typedef  TYPE_1__ Fts5Index ;
typedef  TYPE_2__ Fts5Config ;

/* Variables and functions */
 int /*<<< orphan*/  fts5IndexPrepareStmt (TYPE_1__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static sqlite3_stmt *fts5IdxSelectStmt(Fts5Index *p){
  if( p->pIdxSelect==0 ){
    Fts5Config *pConfig = p->pConfig;
    fts5IndexPrepareStmt(p, &p->pIdxSelect, sqlite3_mprintf(
          "SELECT pgno FROM '%q'.'%q_idx' WHERE "
          "segid=? AND term<=? ORDER BY term DESC LIMIT 1",
          pConfig->zDb, pConfig->zName
    ));
  }
  return p->pIdxSelect;
}