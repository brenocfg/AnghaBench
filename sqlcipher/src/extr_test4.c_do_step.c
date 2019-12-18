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
struct TYPE_3__ {scalar_t__ pStmt; char* zErr; char* zStaticErr; scalar_t__ rc; int argc; char** argv; int /*<<< orphan*/ * colv; } ;
typedef  TYPE_1__ Thread ;

/* Variables and functions */
 scalar_t__ SQLITE_ERROR ; 
 scalar_t__ SQLITE_ROW ; 
 int sqlite3_column_count (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_column_name (scalar_t__,int) ; 
 scalar_t__ sqlite3_column_text (scalar_t__,int) ; 
 int sqlite3_data_count (scalar_t__) ; 
 scalar_t__ sqlite3_step (scalar_t__) ; 

__attribute__((used)) static void do_step(Thread *p){
  int i;
  if( p->pStmt==0 ){
    p->zErr = p->zStaticErr = "no virtual machine available";
    p->rc = SQLITE_ERROR;
    return;
  }
  p->rc = sqlite3_step(p->pStmt);
  if( p->rc==SQLITE_ROW ){
    p->argc = sqlite3_column_count(p->pStmt);
    for(i=0; i<sqlite3_data_count(p->pStmt); i++){
      p->argv[i] = (char*)sqlite3_column_text(p->pStmt, i);
    }
    for(i=0; i<p->argc; i++){
      p->colv[i] = sqlite3_column_name(p->pStmt, i);
    }
  }
}