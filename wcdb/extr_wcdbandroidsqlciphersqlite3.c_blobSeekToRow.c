#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  char* sqlite3_int64 ;
struct TYPE_13__ {int /*<<< orphan*/  pCursor; } ;
struct TYPE_14__ {int nHdrParsed; int* aType; size_t nField; TYPE_4__ uc; } ;
typedef  TYPE_5__ VdbeCursor ;
struct TYPE_15__ {int pc; TYPE_5__** apCsr; TYPE_3__* aOp; TYPE_2__* aMem; } ;
typedef  TYPE_6__ Vdbe ;
struct TYPE_16__ {int iCol; int iOffset; int /*<<< orphan*/  db; scalar_t__ pStmt; int /*<<< orphan*/  pCsr; int /*<<< orphan*/  nByte; } ;
struct TYPE_12__ {scalar_t__ opcode; } ;
struct TYPE_10__ {char* i; } ;
struct TYPE_11__ {TYPE_1__ u; int /*<<< orphan*/  flags; } ;
typedef  TYPE_7__ Incrblob ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_Int ; 
 scalar_t__ OP_NotExists ; 
 int SQLITE_DONE ; 
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3BtreeIncrblobCursor (int /*<<< orphan*/ ) ; 
 char* sqlite3MPrintf (int /*<<< orphan*/ ,char*,char*) ; 
 int sqlite3VdbeExec (TYPE_6__*) ; 
 int /*<<< orphan*/  sqlite3VdbeSerialTypeLen (int) ; 
 char* sqlite3_errmsg (int /*<<< orphan*/ ) ; 
 int sqlite3_finalize (scalar_t__) ; 
 int sqlite3_step (scalar_t__) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static int blobSeekToRow(Incrblob *p, sqlite3_int64 iRow, char **pzErr){
  int rc;                         /* Error code */
  char *zErr = 0;                 /* Error message */
  Vdbe *v = (Vdbe *)p->pStmt;

  /* Set the value of register r[1] in the SQL statement to integer iRow. 
  ** This is done directly as a performance optimization
  */
  v->aMem[1].flags = MEM_Int;
  v->aMem[1].u.i = iRow;

  /* If the statement has been run before (and is paused at the OP_ResultRow)
  ** then back it up to the point where it does the OP_NotExists.  This could
  ** have been down with an extra OP_Goto, but simply setting the program
  ** counter is faster. */
  if( v->pc>4 ){
    v->pc = 4;
    assert( v->aOp[v->pc].opcode==OP_NotExists );
    rc = sqlite3VdbeExec(v);
  }else{
    rc = sqlite3_step(p->pStmt);
  }
  if( rc==SQLITE_ROW ){
    VdbeCursor *pC = v->apCsr[0];
    u32 type = pC->nHdrParsed>p->iCol ? pC->aType[p->iCol] : 0;
    testcase( pC->nHdrParsed==p->iCol );
    testcase( pC->nHdrParsed==p->iCol+1 );
    if( type<12 ){
      zErr = sqlite3MPrintf(p->db, "cannot open value of type %s",
          type==0?"null": type==7?"real": "integer"
      );
      rc = SQLITE_ERROR;
      sqlite3_finalize(p->pStmt);
      p->pStmt = 0;
    }else{
      p->iOffset = pC->aType[p->iCol + pC->nField];
      p->nByte = sqlite3VdbeSerialTypeLen(type);
      p->pCsr =  pC->uc.pCursor;
      sqlite3BtreeIncrblobCursor(p->pCsr);
    }
  }

  if( rc==SQLITE_ROW ){
    rc = SQLITE_OK;
  }else if( p->pStmt ){
    rc = sqlite3_finalize(p->pStmt);
    p->pStmt = 0;
    if( rc==SQLITE_OK ){
      zErr = sqlite3MPrintf(p->db, "no such rowid: %lld", iRow);
      rc = SQLITE_ERROR;
    }else{
      zErr = sqlite3MPrintf(p->db, "%s", sqlite3_errmsg(p->db));
    }
  }

  assert( rc!=SQLITE_OK || zErr==0 );
  assert( rc!=SQLITE_ROW && rc!=SQLITE_DONE );

  *pzErr = zErr;
  return rc;
}