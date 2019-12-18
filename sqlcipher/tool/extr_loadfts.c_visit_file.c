#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int nRowPerTrans; int /*<<< orphan*/  db; int /*<<< orphan*/  pInsert; } ;
typedef  TYPE_1__ VisitContext ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  sqlite3_bind_text (int /*<<< orphan*/ ,int,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_exec (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sqlite3_last_insert_rowid (int /*<<< orphan*/ ) ; 
 int sqlite3_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_step (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite_error_out (char*,int /*<<< orphan*/ ) ; 

void visit_file(void *pCtx, const char *zPath){
  int rc;
  VisitContext *p = (VisitContext*)pCtx;
  /* printf("%s\n", zPath); */
  sqlite3_bind_text(p->pInsert, 1, zPath, -1, SQLITE_STATIC);
  sqlite3_step(p->pInsert);
  rc = sqlite3_reset(p->pInsert);
  if( rc!=SQLITE_OK ){
    sqlite_error_out("insert", p->db);
  }else if( p->nRowPerTrans>0 
         && (sqlite3_last_insert_rowid(p->db) % p->nRowPerTrans)==0 
  ){
    sqlite3_exec(p->db, "COMMIT ; BEGIN", 0, 0, 0);
  }
}