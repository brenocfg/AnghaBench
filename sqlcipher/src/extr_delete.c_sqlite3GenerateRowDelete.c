#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  scalar_t__ i16 ;
typedef  int /*<<< orphan*/  Vdbe ;
typedef  int /*<<< orphan*/  Trigger ;
struct TYPE_22__ {int nCol; scalar_t__ pSelect; int /*<<< orphan*/  zName; } ;
typedef  TYPE_1__ Table ;
struct TYPE_23__ {int nMem; scalar_t__ nested; int /*<<< orphan*/ * pVdbe; } ;
typedef  TYPE_2__ Parse ;

/* Variables and functions */
 scalar_t__ HasRowid (TYPE_1__*) ; 
 int MASKBIT32 (int) ; 
 scalar_t__ ONEPASS_MULTI ; 
 scalar_t__ ONEPASS_OFF ; 
 scalar_t__ OPFLAG_AUXDELETE ; 
 int OPFLAG_NCHANGE ; 
 scalar_t__ OPFLAG_SAVEPOSITION ; 
 int /*<<< orphan*/  OP_Copy ; 
 int /*<<< orphan*/  OP_Delete ; 
 scalar_t__ OP_NotExists ; 
 scalar_t__ OP_NotFound ; 
 int /*<<< orphan*/  P4_TABLE ; 
 int /*<<< orphan*/  TK_DELETE ; 
 int TRIGGER_AFTER ; 
 int TRIGGER_BEFORE ; 
 int /*<<< orphan*/  VdbeCoverageIf (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  VdbeModuleComment (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3CodeRowTrigger (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_1__*,int,scalar_t__,int) ; 
 int /*<<< orphan*/  sqlite3ExprCodeGetColumnOfTable (int /*<<< orphan*/ *,TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  sqlite3FkActions (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3FkCheck (TYPE_2__*,TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sqlite3FkOldmask (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ sqlite3FkRequired (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3GenerateRowIndexDelete (TYPE_2__*,TYPE_1__*,int,int,int /*<<< orphan*/ ,int) ; 
 int sqlite3TriggerColmask (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp4Int (int /*<<< orphan*/ *,scalar_t__,int,int,int,scalar_t__) ; 
 int /*<<< orphan*/  sqlite3VdbeAppendP4 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeChangeP5 (int /*<<< orphan*/ *,scalar_t__) ; 
 int sqlite3VdbeCurrentAddr (int /*<<< orphan*/ *) ; 
 int sqlite3VdbeMakeLabel (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3VdbeResolveLabel (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_stricmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  testcase (int) ; 

void sqlite3GenerateRowDelete(
  Parse *pParse,     /* Parsing context */
  Table *pTab,       /* Table containing the row to be deleted */
  Trigger *pTrigger, /* List of triggers to (potentially) fire */
  int iDataCur,      /* Cursor from which column data is extracted */
  int iIdxCur,       /* First index cursor */
  int iPk,           /* First memory cell containing the PRIMARY KEY */
  i16 nPk,           /* Number of PRIMARY KEY memory cells */
  u8 count,          /* If non-zero, increment the row change counter */
  u8 onconf,         /* Default ON CONFLICT policy for triggers */
  u8 eMode,          /* ONEPASS_OFF, _SINGLE, or _MULTI.  See above */
  int iIdxNoSeek     /* Cursor number of cursor that does not need seeking */
){
  Vdbe *v = pParse->pVdbe;        /* Vdbe */
  int iOld = 0;                   /* First register in OLD.* array */
  int iLabel;                     /* Label resolved to end of generated code */
  u8 opSeek;                      /* Seek opcode */

  /* Vdbe is guaranteed to have been allocated by this stage. */
  assert( v );
  VdbeModuleComment((v, "BEGIN: GenRowDel(%d,%d,%d,%d)",
                         iDataCur, iIdxCur, iPk, (int)nPk));

  /* Seek cursor iCur to the row to delete. If this row no longer exists 
  ** (this can happen if a trigger program has already deleted it), do
  ** not attempt to delete it or fire any DELETE triggers.  */
  iLabel = sqlite3VdbeMakeLabel(pParse);
  opSeek = HasRowid(pTab) ? OP_NotExists : OP_NotFound;
  if( eMode==ONEPASS_OFF ){
    sqlite3VdbeAddOp4Int(v, opSeek, iDataCur, iLabel, iPk, nPk);
    VdbeCoverageIf(v, opSeek==OP_NotExists);
    VdbeCoverageIf(v, opSeek==OP_NotFound);
  }
 
  /* If there are any triggers to fire, allocate a range of registers to
  ** use for the old.* references in the triggers.  */
  if( sqlite3FkRequired(pParse, pTab, 0, 0) || pTrigger ){
    u32 mask;                     /* Mask of OLD.* columns in use */
    int iCol;                     /* Iterator used while populating OLD.* */
    int addrStart;                /* Start of BEFORE trigger programs */

    /* TODO: Could use temporary registers here. Also could attempt to
    ** avoid copying the contents of the rowid register.  */
    mask = sqlite3TriggerColmask(
        pParse, pTrigger, 0, 0, TRIGGER_BEFORE|TRIGGER_AFTER, pTab, onconf
    );
    mask |= sqlite3FkOldmask(pParse, pTab);
    iOld = pParse->nMem+1;
    pParse->nMem += (1 + pTab->nCol);

    /* Populate the OLD.* pseudo-table register array. These values will be 
    ** used by any BEFORE and AFTER triggers that exist.  */
    sqlite3VdbeAddOp2(v, OP_Copy, iPk, iOld);
    for(iCol=0; iCol<pTab->nCol; iCol++){
      testcase( mask!=0xffffffff && iCol==31 );
      testcase( mask!=0xffffffff && iCol==32 );
      if( mask==0xffffffff || (iCol<=31 && (mask & MASKBIT32(iCol))!=0) ){
        sqlite3ExprCodeGetColumnOfTable(v, pTab, iDataCur, iCol, iOld+iCol+1);
      }
    }

    /* Invoke BEFORE DELETE trigger programs. */
    addrStart = sqlite3VdbeCurrentAddr(v);
    sqlite3CodeRowTrigger(pParse, pTrigger, 
        TK_DELETE, 0, TRIGGER_BEFORE, pTab, iOld, onconf, iLabel
    );

    /* If any BEFORE triggers were coded, then seek the cursor to the 
    ** row to be deleted again. It may be that the BEFORE triggers moved
    ** the cursor or already deleted the row that the cursor was
    ** pointing to.
    **
    ** Also disable the iIdxNoSeek optimization since the BEFORE trigger
    ** may have moved that cursor.
    */
    if( addrStart<sqlite3VdbeCurrentAddr(v) ){
      sqlite3VdbeAddOp4Int(v, opSeek, iDataCur, iLabel, iPk, nPk);
      VdbeCoverageIf(v, opSeek==OP_NotExists);
      VdbeCoverageIf(v, opSeek==OP_NotFound);
      testcase( iIdxNoSeek>=0 );
      iIdxNoSeek = -1;
    }

    /* Do FK processing. This call checks that any FK constraints that
    ** refer to this table (i.e. constraints attached to other tables) 
    ** are not violated by deleting this row.  */
    sqlite3FkCheck(pParse, pTab, iOld, 0, 0, 0);
  }

  /* Delete the index and table entries. Skip this step if pTab is really
  ** a view (in which case the only effect of the DELETE statement is to
  ** fire the INSTEAD OF triggers).  
  **
  ** If variable 'count' is non-zero, then this OP_Delete instruction should
  ** invoke the update-hook. The pre-update-hook, on the other hand should
  ** be invoked unless table pTab is a system table. The difference is that
  ** the update-hook is not invoked for rows removed by REPLACE, but the 
  ** pre-update-hook is.
  */ 
  if( pTab->pSelect==0 ){
    u8 p5 = 0;
    sqlite3GenerateRowIndexDelete(pParse, pTab, iDataCur, iIdxCur,0,iIdxNoSeek);
    sqlite3VdbeAddOp2(v, OP_Delete, iDataCur, (count?OPFLAG_NCHANGE:0));
    if( pParse->nested==0 || 0==sqlite3_stricmp(pTab->zName, "sqlite_stat1") ){
      sqlite3VdbeAppendP4(v, (char*)pTab, P4_TABLE);
    }
    if( eMode!=ONEPASS_OFF ){
      sqlite3VdbeChangeP5(v, OPFLAG_AUXDELETE);
    }
    if( iIdxNoSeek>=0 && iIdxNoSeek!=iDataCur ){
      sqlite3VdbeAddOp1(v, OP_Delete, iIdxNoSeek);
    }
    if( eMode==ONEPASS_MULTI ) p5 |= OPFLAG_SAVEPOSITION;
    sqlite3VdbeChangeP5(v, p5);
  }

  /* Do any ON CASCADE, SET NULL or SET DEFAULT operations required to
  ** handle rows (possibly in other tables) that refer via a foreign key
  ** to the row just deleted. */ 
  sqlite3FkActions(pParse, pTab, 0, iOld, 0, 0);

  /* Invoke AFTER DELETE trigger programs. */
  sqlite3CodeRowTrigger(pParse, pTrigger, 
      TK_DELETE, 0, TRIGGER_AFTER, pTab, iOld, onconf, iLabel
  );

  /* Jump here if the row had already been deleted before any BEFORE
  ** trigger programs were invoked. Or if a trigger program throws a 
  ** RAISE(IGNORE) exception.  */
  sqlite3VdbeResolveLabel(v, iLabel);
  VdbeModuleComment((v, "END: GenRowDel()"));
}