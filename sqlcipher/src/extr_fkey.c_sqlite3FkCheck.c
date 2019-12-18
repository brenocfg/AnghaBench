#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_57__   TYPE_9__ ;
typedef  struct TYPE_56__   TYPE_8__ ;
typedef  struct TYPE_55__   TYPE_7__ ;
typedef  struct TYPE_54__   TYPE_6__ ;
typedef  struct TYPE_53__   TYPE_5__ ;
typedef  struct TYPE_52__   TYPE_4__ ;
typedef  struct TYPE_51__   TYPE_3__ ;
typedef  struct TYPE_50__   TYPE_2__ ;
typedef  struct TYPE_49__   TYPE_1__ ;
typedef  struct TYPE_48__   TYPE_10__ ;

/* Type definitions */
struct SrcList_item {scalar_t__ zName; scalar_t__ iCursor; TYPE_1__* pTab; } ;
struct TYPE_53__ {int flags; scalar_t__ mallocFailed; scalar_t__ xAuth; TYPE_2__* aDb; } ;
typedef  TYPE_5__ sqlite3 ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_54__ {int iPKey; int /*<<< orphan*/  zName; int /*<<< orphan*/  tnum; TYPE_4__* aCol; TYPE_10__* pFKey; int /*<<< orphan*/  pSchema; } ;
typedef  TYPE_6__ Table ;
struct TYPE_57__ {size_t* aiColumn; } ;
struct TYPE_56__ {int disableTriggers; int /*<<< orphan*/  nTab; int /*<<< orphan*/  isMultiWrite; int /*<<< orphan*/  pToplevel; TYPE_5__* db; } ;
struct TYPE_55__ {struct SrcList_item* a; } ;
struct TYPE_52__ {char* zName; } ;
struct TYPE_51__ {int iFrom; } ;
struct TYPE_50__ {char* zDbSName; } ;
struct TYPE_49__ {int /*<<< orphan*/  nTabRef; scalar_t__ zName; } ;
struct TYPE_48__ {int nCol; int isDeferred; int* aAction; TYPE_1__* pFrom; struct TYPE_48__* pNextTo; TYPE_3__* aCol; int /*<<< orphan*/  zTo; struct TYPE_48__* pNextFrom; } ;
typedef  TYPE_7__ SrcList ;
typedef  TYPE_8__ Parse ;
typedef  TYPE_9__ Index ;
typedef  TYPE_10__ FKey ;

/* Variables and functions */
 int OE_Cascade ; 
 int OE_SetNull ; 
 int /*<<< orphan*/  OP_FkCounter ; 
 int /*<<< orphan*/  OP_IsNull ; 
 int SQLITE_DeferFKs ; 
 int SQLITE_ForeignKeys ; 
 int SQLITE_IGNORE ; 
 int /*<<< orphan*/  VdbeCoverage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ fkChildIsModified (TYPE_6__*,TYPE_10__*,int*,int) ; 
 int /*<<< orphan*/  fkLookupParent (TYPE_8__*,int,TYPE_6__*,TYPE_9__*,TYPE_10__*,int*,int,int,int) ; 
 scalar_t__ fkParentIsModified (TYPE_6__*,TYPE_10__*,int*,int) ; 
 int /*<<< orphan*/  fkScanChildren (TYPE_8__*,TYPE_7__*,TYPE_6__*,TYPE_9__*,TYPE_10__*,int*,int,int) ; 
 int /*<<< orphan*/  isSetNullAction (TYPE_8__*,TYPE_10__*) ; 
 int sqlite3AuthReadCol (TYPE_8__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sqlite3DbFree (TYPE_5__*,int*) ; 
 TYPE_6__* sqlite3FindTable (TYPE_5__*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ sqlite3FkLocateIndex (TYPE_8__*,TYPE_6__*,TYPE_10__*,TYPE_9__**,int**) ; 
 TYPE_10__* sqlite3FkReferences (TYPE_6__*) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (TYPE_8__*) ; 
 TYPE_6__* sqlite3LocateTable (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  sqlite3MayAbort (TYPE_8__*) ; 
 int sqlite3SchemaToIndex (TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_7__* sqlite3SrcListAppend (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3SrcListDelete (TYPE_5__*,TYPE_7__*) ; 
 int /*<<< orphan*/  sqlite3TableLock (TYPE_8__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int sqlite3VdbeCurrentAddr (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_stricmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sqlite3FkCheck(
  Parse *pParse,                  /* Parse context */
  Table *pTab,                    /* Row is being deleted from this table */ 
  int regOld,                     /* Previous row data is stored here */
  int regNew,                     /* New row data is stored here */
  int *aChange,                   /* Array indicating UPDATEd columns (or 0) */
  int bChngRowid                  /* True if rowid is UPDATEd */
){
  sqlite3 *db = pParse->db;       /* Database handle */
  FKey *pFKey;                    /* Used to iterate through FKs */
  int iDb;                        /* Index of database containing pTab */
  const char *zDb;                /* Name of database containing pTab */
  int isIgnoreErrors = pParse->disableTriggers;

  /* Exactly one of regOld and regNew should be non-zero. */
  assert( (regOld==0)!=(regNew==0) );

  /* If foreign-keys are disabled, this function is a no-op. */
  if( (db->flags&SQLITE_ForeignKeys)==0 ) return;

  iDb = sqlite3SchemaToIndex(db, pTab->pSchema);
  zDb = db->aDb[iDb].zDbSName;

  /* Loop through all the foreign key constraints for which pTab is the
  ** child table (the table that the foreign key definition is part of).  */
  for(pFKey=pTab->pFKey; pFKey; pFKey=pFKey->pNextFrom){
    Table *pTo;                   /* Parent table of foreign key pFKey */
    Index *pIdx = 0;              /* Index on key columns in pTo */
    int *aiFree = 0;
    int *aiCol;
    int iCol;
    int i;
    int bIgnore = 0;

    if( aChange 
     && sqlite3_stricmp(pTab->zName, pFKey->zTo)!=0
     && fkChildIsModified(pTab, pFKey, aChange, bChngRowid)==0 
    ){
      continue;
    }

    /* Find the parent table of this foreign key. Also find a unique index 
    ** on the parent key columns in the parent table. If either of these 
    ** schema items cannot be located, set an error in pParse and return 
    ** early.  */
    if( pParse->disableTriggers ){
      pTo = sqlite3FindTable(db, pFKey->zTo, zDb);
    }else{
      pTo = sqlite3LocateTable(pParse, 0, pFKey->zTo, zDb);
    }
    if( !pTo || sqlite3FkLocateIndex(pParse, pTo, pFKey, &pIdx, &aiFree) ){
      assert( isIgnoreErrors==0 || (regOld!=0 && regNew==0) );
      if( !isIgnoreErrors || db->mallocFailed ) return;
      if( pTo==0 ){
        /* If isIgnoreErrors is true, then a table is being dropped. In this
        ** case SQLite runs a "DELETE FROM xxx" on the table being dropped
        ** before actually dropping it in order to check FK constraints.
        ** If the parent table of an FK constraint on the current table is
        ** missing, behave as if it is empty. i.e. decrement the relevant
        ** FK counter for each row of the current table with non-NULL keys.
        */
        Vdbe *v = sqlite3GetVdbe(pParse);
        int iJump = sqlite3VdbeCurrentAddr(v) + pFKey->nCol + 1;
        for(i=0; i<pFKey->nCol; i++){
          int iReg = pFKey->aCol[i].iFrom + regOld + 1;
          sqlite3VdbeAddOp2(v, OP_IsNull, iReg, iJump); VdbeCoverage(v);
        }
        sqlite3VdbeAddOp2(v, OP_FkCounter, pFKey->isDeferred, -1);
      }
      continue;
    }
    assert( pFKey->nCol==1 || (aiFree && pIdx) );

    if( aiFree ){
      aiCol = aiFree;
    }else{
      iCol = pFKey->aCol[0].iFrom;
      aiCol = &iCol;
    }
    for(i=0; i<pFKey->nCol; i++){
      if( aiCol[i]==pTab->iPKey ){
        aiCol[i] = -1;
      }
      assert( pIdx==0 || pIdx->aiColumn[i]>=0 );
#ifndef SQLITE_OMIT_AUTHORIZATION
      /* Request permission to read the parent key columns. If the 
      ** authorization callback returns SQLITE_IGNORE, behave as if any
      ** values read from the parent table are NULL. */
      if( db->xAuth ){
        int rcauth;
        char *zCol = pTo->aCol[pIdx ? pIdx->aiColumn[i] : pTo->iPKey].zName;
        rcauth = sqlite3AuthReadCol(pParse, pTo->zName, zCol, iDb);
        bIgnore = (rcauth==SQLITE_IGNORE);
      }
#endif
    }

    /* Take a shared-cache advisory read-lock on the parent table. Allocate 
    ** a cursor to use to search the unique index on the parent key columns 
    ** in the parent table.  */
    sqlite3TableLock(pParse, iDb, pTo->tnum, 0, pTo->zName);
    pParse->nTab++;

    if( regOld!=0 ){
      /* A row is being removed from the child table. Search for the parent.
      ** If the parent does not exist, removing the child row resolves an 
      ** outstanding foreign key constraint violation. */
      fkLookupParent(pParse, iDb, pTo, pIdx, pFKey, aiCol, regOld, -1, bIgnore);
    }
    if( regNew!=0 && !isSetNullAction(pParse, pFKey) ){
      /* A row is being added to the child table. If a parent row cannot
      ** be found, adding the child row has violated the FK constraint. 
      **
      ** If this operation is being performed as part of a trigger program
      ** that is actually a "SET NULL" action belonging to this very 
      ** foreign key, then omit this scan altogether. As all child key
      ** values are guaranteed to be NULL, it is not possible for adding
      ** this row to cause an FK violation.  */
      fkLookupParent(pParse, iDb, pTo, pIdx, pFKey, aiCol, regNew, +1, bIgnore);
    }

    sqlite3DbFree(db, aiFree);
  }

  /* Loop through all the foreign key constraints that refer to this table.
  ** (the "child" constraints) */
  for(pFKey = sqlite3FkReferences(pTab); pFKey; pFKey=pFKey->pNextTo){
    Index *pIdx = 0;              /* Foreign key index for pFKey */
    SrcList *pSrc;
    int *aiCol = 0;

    if( aChange && fkParentIsModified(pTab, pFKey, aChange, bChngRowid)==0 ){
      continue;
    }

    if( !pFKey->isDeferred && !(db->flags & SQLITE_DeferFKs) 
     && !pParse->pToplevel && !pParse->isMultiWrite 
    ){
      assert( regOld==0 && regNew!=0 );
      /* Inserting a single row into a parent table cannot cause (or fix)
      ** an immediate foreign key violation. So do nothing in this case.  */
      continue;
    }

    if( sqlite3FkLocateIndex(pParse, pTab, pFKey, &pIdx, &aiCol) ){
      if( !isIgnoreErrors || db->mallocFailed ) return;
      continue;
    }
    assert( aiCol || pFKey->nCol==1 );

    /* Create a SrcList structure containing the child table.  We need the
    ** child table as a SrcList for sqlite3WhereBegin() */
    pSrc = sqlite3SrcListAppend(pParse, 0, 0, 0);
    if( pSrc ){
      struct SrcList_item *pItem = pSrc->a;
      pItem->pTab = pFKey->pFrom;
      pItem->zName = pFKey->pFrom->zName;
      pItem->pTab->nTabRef++;
      pItem->iCursor = pParse->nTab++;
  
      if( regNew!=0 ){
        fkScanChildren(pParse, pSrc, pTab, pIdx, pFKey, aiCol, regNew, -1);
      }
      if( regOld!=0 ){
        int eAction = pFKey->aAction[aChange!=0];
        fkScanChildren(pParse, pSrc, pTab, pIdx, pFKey, aiCol, regOld, 1);
        /* If this is a deferred FK constraint, or a CASCADE or SET NULL
        ** action applies, then any foreign key violations caused by
        ** removing the parent key will be rectified by the action trigger.
        ** So do not set the "may-abort" flag in this case.
        **
        ** Note 1: If the FK is declared "ON UPDATE CASCADE", then the
        ** may-abort flag will eventually be set on this statement anyway
        ** (when this function is called as part of processing the UPDATE
        ** within the action trigger).
        **
        ** Note 2: At first glance it may seem like SQLite could simply omit
        ** all OP_FkCounter related scans when either CASCADE or SET NULL
        ** applies. The trouble starts if the CASCADE or SET NULL action 
        ** trigger causes other triggers or action rules attached to the 
        ** child table to fire. In these cases the fk constraint counters
        ** might be set incorrectly if any OP_FkCounter related scans are 
        ** omitted.  */
        if( !pFKey->isDeferred && eAction!=OE_Cascade && eAction!=OE_SetNull ){
          sqlite3MayAbort(pParse);
        }
      }
      pItem->zName = 0;
      sqlite3SrcListDelete(db, pSrc);
    }
    sqlite3DbFree(db, aiCol);
  }
}