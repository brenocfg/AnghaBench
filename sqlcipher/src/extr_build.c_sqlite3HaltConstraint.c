#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  i8 ;
typedef  int /*<<< orphan*/  Vdbe ;
typedef  int /*<<< orphan*/  Parse ;

/* Variables and functions */
 int OE_Abort ; 
 int /*<<< orphan*/  OP_Halt ; 
 int SQLITE_CONSTRAINT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3MayAbort (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeChangeP5 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void sqlite3HaltConstraint(
  Parse *pParse,    /* Parsing context */
  int errCode,      /* extended error code */
  int onError,      /* Constraint type */
  char *p4,         /* Error message */
  i8 p4type,        /* P4_STATIC or P4_TRANSIENT */
  u8 p5Errmsg       /* P5_ErrMsg type */
){
  Vdbe *v = sqlite3GetVdbe(pParse);
  assert( (errCode&0xff)==SQLITE_CONSTRAINT );
  if( onError==OE_Abort ){
    sqlite3MayAbort(pParse);
  }
  sqlite3VdbeAddOp4(v, OP_Halt, errCode, onError, 0, p4, p4type);
  sqlite3VdbeChangeP5(v, p5Errmsg);
}