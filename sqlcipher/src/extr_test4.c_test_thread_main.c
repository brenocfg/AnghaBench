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
struct TYPE_3__ {scalar_t__ zErr; int completed; int opnum; scalar_t__ zStaticErr; scalar_t__ db; scalar_t__ pStmt; int /*<<< orphan*/  (* xOp ) (TYPE_1__*) ;int /*<<< orphan*/  zFilename; } ;
typedef  TYPE_1__ Thread ;

/* Variables and functions */
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  sched_yield () ; 
 int /*<<< orphan*/  sqlite3_close (scalar_t__) ; 
 scalar_t__ sqlite3_errcode (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_errmsg (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_finalize (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_free (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_open (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  sqlite3_thread_cleanup () ; 
 scalar_t__ strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static void *test_thread_main(void *pArg){
  Thread *p = (Thread*)pArg;
  if( p->db ){
    sqlite3_close(p->db);
  }
  sqlite3_open(p->zFilename, &p->db);
  if( SQLITE_OK!=sqlite3_errcode(p->db) ){
    p->zErr = strdup(sqlite3_errmsg(p->db));
    sqlite3_close(p->db);
    p->db = 0;
  }
  p->pStmt = 0;
  p->completed = 1;
  while( p->opnum<=p->completed ) sched_yield();
  while( p->xOp ){
    if( p->zErr && p->zErr!=p->zStaticErr ){
      sqlite3_free(p->zErr);
      p->zErr = 0;
    }
    (*p->xOp)(p);
    p->completed++;
    while( p->opnum<=p->completed ) sched_yield();
  }
  if( p->pStmt ){
    sqlite3_finalize(p->pStmt);
    p->pStmt = 0;
  }
  if( p->db ){
    sqlite3_close(p->db);
    p->db = 0;
  }
  if( p->zErr && p->zErr!=p->zStaticErr ){
    sqlite3_free(p->zErr);
    p->zErr = 0;
  }
  p->completed++;
#ifndef SQLITE_OMIT_DEPRECATED
  sqlite3_thread_cleanup();
#endif
  return 0;
}