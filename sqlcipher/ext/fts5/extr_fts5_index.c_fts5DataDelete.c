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
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_6__ {int /*<<< orphan*/  zName; int /*<<< orphan*/  zDb; } ;
struct TYPE_5__ {scalar_t__ rc; scalar_t__ pDeleter; TYPE_2__* pConfig; } ;
typedef  TYPE_1__ Fts5Index ;
typedef  TYPE_2__ Fts5Config ;

/* Variables and functions */
 scalar_t__ SQLITE_OK ; 
 scalar_t__ fts5IndexPrepareStmt (TYPE_1__*,scalar_t__*,char*) ; 
 int /*<<< orphan*/  sqlite3_bind_int64 (scalar_t__,int,int /*<<< orphan*/ ) ; 
 char* sqlite3_mprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_reset (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_step (scalar_t__) ; 

__attribute__((used)) static void fts5DataDelete(Fts5Index *p, i64 iFirst, i64 iLast){
  if( p->rc!=SQLITE_OK ) return;

  if( p->pDeleter==0 ){
    Fts5Config *pConfig = p->pConfig;
    char *zSql = sqlite3_mprintf(
        "DELETE FROM '%q'.'%q_data' WHERE id>=? AND id<=?", 
          pConfig->zDb, pConfig->zName
    );
    if( fts5IndexPrepareStmt(p, &p->pDeleter, zSql) ) return;
  }

  sqlite3_bind_int64(p->pDeleter, 1, iFirst);
  sqlite3_bind_int64(p->pDeleter, 2, iLast);
  sqlite3_step(p->pDeleter);
  p->rc = sqlite3_reset(p->pDeleter);
}