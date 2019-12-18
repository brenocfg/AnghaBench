#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_11__ ;

/* Type definitions */
struct TYPE_23__ {scalar_t__ busy; } ;
struct TYPE_21__ {scalar_t__ authLevel; } ;
struct TYPE_26__ {scalar_t__ mallocFailed; int nDb; TYPE_3__ init; TYPE_2__* aDb; TYPE_1__ auth; } ;
typedef  TYPE_6__ sqlite3 ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_29__ {int nExpr; TYPE_5__* a; } ;
struct TYPE_28__ {scalar_t__ pToplevel; scalar_t__ nErr; scalar_t__ rc; scalar_t__ nTableLock; int nVtabLock; scalar_t__ pAinc; scalar_t__ nTab; scalar_t__ okConstFactor; TYPE_9__* pConstExpr; int /*<<< orphan*/ * apVtabLock; scalar_t__ isMultiWrite; scalar_t__ mayAbort; int /*<<< orphan*/  writeMask; int /*<<< orphan*/  cookieMask; scalar_t__ nested; TYPE_6__* db; } ;
struct TYPE_27__ {int /*<<< orphan*/  iGeneration; int /*<<< orphan*/  schema_cookie; } ;
struct TYPE_24__ {int /*<<< orphan*/  iConstExprReg; } ;
struct TYPE_25__ {TYPE_4__ u; int /*<<< orphan*/  pExpr; } ;
struct TYPE_22__ {TYPE_7__* pSchema; } ;
struct TYPE_20__ {scalar_t__ opcode; } ;
typedef  TYPE_7__ Schema ;
typedef  TYPE_8__ Parse ;
typedef  TYPE_9__ ExprList ;

/* Variables and functions */
 scalar_t__ DbMaskNonZero (int /*<<< orphan*/ ) ; 
 scalar_t__ DbMaskTest (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OP_Halt ; 
 scalar_t__ OP_Init ; 
 int /*<<< orphan*/  OP_Transaction ; 
 int /*<<< orphan*/  OP_VBegin ; 
 int /*<<< orphan*/  P4_VTAB ; 
 scalar_t__ SQLITE_AUTH_USER ; 
 scalar_t__ SQLITE_DONE ; 
 void* SQLITE_ERROR ; 
 scalar_t__ SQLITE_OK ; 
 scalar_t__ UAUTH_User ; 
 int /*<<< orphan*/  VdbeComment (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  codeTableLocks (TYPE_8__*) ; 
 int /*<<< orphan*/  sqlite3AutoincrementBegin (TYPE_8__*) ; 
 int /*<<< orphan*/  sqlite3ErrorMsg (TYPE_8__*,char*) ; 
 int /*<<< orphan*/  sqlite3ExprCode (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3GetVTable (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (TYPE_8__*) ; 
 int /*<<< orphan*/  sqlite3UserAuthInit (TYPE_6__*) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp0 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp4Int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3VdbeAssertMayAbort (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sqlite3VdbeChangeP5 (int /*<<< orphan*/ *,int) ; 
 TYPE_11__* sqlite3VdbeGetOp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeGoto (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3VdbeJumpHere (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeMakeReady (int /*<<< orphan*/ *,TYPE_8__*) ; 
 int /*<<< orphan*/  sqlite3VdbeUsesBtree (int /*<<< orphan*/ *,int) ; 

void sqlite3FinishCoding(Parse *pParse){
  sqlite3 *db;
  Vdbe *v;

  assert( pParse->pToplevel==0 );
  db = pParse->db;
  if( pParse->nested ) return;
  if( db->mallocFailed || pParse->nErr ){
    if( pParse->rc==SQLITE_OK ) pParse->rc = SQLITE_ERROR;
    return;
  }

  /* Begin by generating some termination code at the end of the
  ** vdbe program
  */
  v = sqlite3GetVdbe(pParse);
  assert( !pParse->isMultiWrite 
       || sqlite3VdbeAssertMayAbort(v, pParse->mayAbort));
  if( v ){
    sqlite3VdbeAddOp0(v, OP_Halt);

#if SQLITE_USER_AUTHENTICATION
    if( pParse->nTableLock>0 && db->init.busy==0 ){
      sqlite3UserAuthInit(db);
      if( db->auth.authLevel<UAUTH_User ){
        sqlite3ErrorMsg(pParse, "user not authenticated");
        pParse->rc = SQLITE_AUTH_USER;
        return;
      }
    }
#endif

    /* The cookie mask contains one bit for each database file open.
    ** (Bit 0 is for main, bit 1 is for temp, and so forth.)  Bits are
    ** set for each database that is used.  Generate code to start a
    ** transaction on each used database and to verify the schema cookie
    ** on each used database.
    */
    if( db->mallocFailed==0 
     && (DbMaskNonZero(pParse->cookieMask) || pParse->pConstExpr)
    ){
      int iDb, i;
      assert( sqlite3VdbeGetOp(v, 0)->opcode==OP_Init );
      sqlite3VdbeJumpHere(v, 0);
      for(iDb=0; iDb<db->nDb; iDb++){
        Schema *pSchema;
        if( DbMaskTest(pParse->cookieMask, iDb)==0 ) continue;
        sqlite3VdbeUsesBtree(v, iDb);
        pSchema = db->aDb[iDb].pSchema;
        sqlite3VdbeAddOp4Int(v,
          OP_Transaction,                    /* Opcode */
          iDb,                               /* P1 */
          DbMaskTest(pParse->writeMask,iDb), /* P2 */
          pSchema->schema_cookie,            /* P3 */
          pSchema->iGeneration               /* P4 */
        );
        if( db->init.busy==0 ) sqlite3VdbeChangeP5(v, 1);
        VdbeComment((v,
              "usesStmtJournal=%d", pParse->mayAbort && pParse->isMultiWrite));
      }
#ifndef SQLITE_OMIT_VIRTUALTABLE
      for(i=0; i<pParse->nVtabLock; i++){
        char *vtab = (char *)sqlite3GetVTable(db, pParse->apVtabLock[i]);
        sqlite3VdbeAddOp4(v, OP_VBegin, 0, 0, 0, vtab, P4_VTAB);
      }
      pParse->nVtabLock = 0;
#endif

      /* Once all the cookies have been verified and transactions opened, 
      ** obtain the required table-locks. This is a no-op unless the 
      ** shared-cache feature is enabled.
      */
      codeTableLocks(pParse);

      /* Initialize any AUTOINCREMENT data structures required.
      */
      sqlite3AutoincrementBegin(pParse);

      /* Code constant expressions that where factored out of inner loops */
      if( pParse->pConstExpr ){
        ExprList *pEL = pParse->pConstExpr;
        pParse->okConstFactor = 0;
        for(i=0; i<pEL->nExpr; i++){
          sqlite3ExprCode(pParse, pEL->a[i].pExpr, pEL->a[i].u.iConstExprReg);
        }
      }

      /* Finally, jump back to the beginning of the executable code. */
      sqlite3VdbeGoto(v, 1);
    }
  }


  /* Get the VDBE program ready for execution
  */
  if( v && pParse->nErr==0 && !db->mallocFailed ){
    /* A minimum of one cursor is required if autoincrement is used
    *  See ticket [a696379c1f08866] */
    assert( pParse->pAinc==0 || pParse->nTab>0 );
    sqlite3VdbeMakeReady(v, pParse);
    pParse->rc = SQLITE_DONE;
  }else{
    pParse->rc = SQLITE_ERROR;
  }
}