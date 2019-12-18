#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_9__ {int /*<<< orphan*/  pnBytesFreed; } ;
typedef  TYPE_1__ sqlite3 ;
typedef  int /*<<< orphan*/  VTable ;
typedef  int /*<<< orphan*/  Mem ;
typedef  int /*<<< orphan*/  KeyInfo ;
typedef  int /*<<< orphan*/  FuncDef ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
#define  P4_DYNAMIC 138 
#define  P4_DYNBLOB 137 
#define  P4_EXPR 136 
#define  P4_FUNCCTX 135 
#define  P4_FUNCDEF 134 
#define  P4_INT64 133 
#define  P4_INTARRAY 132 
#define  P4_KEYINFO 131 
#define  P4_MEM 130 
#define  P4_REAL 129 
#define  P4_VTAB 128 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  freeEphemeralFunction (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freeP4FuncCtx (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freeP4Mem (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3DbFree (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  sqlite3ExprDelete (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3KeyInfoUnref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3ValueFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VtabUnlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void freeP4(sqlite3 *db, int p4type, void *p4){
  assert( db );
  switch( p4type ){
    case P4_FUNCCTX: {
      freeP4FuncCtx(db, (sqlite3_context*)p4);
      break;
    }
    case P4_REAL:
    case P4_INT64:
    case P4_DYNAMIC:
    case P4_DYNBLOB:
    case P4_INTARRAY: {
      sqlite3DbFree(db, p4);
      break;
    }
    case P4_KEYINFO: {
      if( db->pnBytesFreed==0 ) sqlite3KeyInfoUnref((KeyInfo*)p4);
      break;
    }
#ifdef SQLITE_ENABLE_CURSOR_HINTS
    case P4_EXPR: {
      sqlite3ExprDelete(db, (Expr*)p4);
      break;
    }
#endif
    case P4_FUNCDEF: {
      freeEphemeralFunction(db, (FuncDef*)p4);
      break;
    }
    case P4_MEM: {
      if( db->pnBytesFreed==0 ){
        sqlite3ValueFree((sqlite3_value*)p4);
      }else{
        freeP4Mem(db, (Mem*)p4);
      }
      break;
    }
    case P4_VTAB : {
      if( db->pnBytesFreed==0 ) sqlite3VtabUnlock((VTable *)p4);
      break;
    }
  }
}