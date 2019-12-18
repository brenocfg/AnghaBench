#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zBuf ;
typedef  int u32 ;
typedef  int u16 ;
struct SrcList_item {char const* zName; char const* zAlias; int /*<<< orphan*/  pTab; TYPE_1__* pSelect; } ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_20__ {int /*<<< orphan*/  idxStr; int /*<<< orphan*/  idxNum; } ;
struct TYPE_19__ {scalar_t__ nEq; TYPE_9__* pIndex; } ;
struct TYPE_21__ {TYPE_3__ vtab; TYPE_2__ btree; } ;
struct TYPE_22__ {int wsFlags; int nOut; TYPE_4__ u; } ;
typedef  TYPE_5__ WhereLoop ;
struct TYPE_23__ {size_t iFrom; TYPE_5__* pWLoop; } ;
typedef  TYPE_6__ WhereLevel ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_26__ {char const* zName; } ;
struct TYPE_25__ {int /*<<< orphan*/  addrExplain; int /*<<< orphan*/ * db; int /*<<< orphan*/ * pVdbe; } ;
struct TYPE_24__ {struct SrcList_item* a; } ;
struct TYPE_18__ {char const* selId; } ;
struct TYPE_17__ {int explain; } ;
typedef  int /*<<< orphan*/  StrAccum ;
typedef  TYPE_7__ SrcList ;
typedef  TYPE_8__ Parse ;
typedef  TYPE_9__ Index ;

/* Variables and functions */
 int /*<<< orphan*/  HasRowid (int /*<<< orphan*/ ) ; 
 scalar_t__ IsPrimaryKeyIndex (TYPE_9__*) ; 
 int /*<<< orphan*/  OP_Explain ; 
 int /*<<< orphan*/  P4_DYNAMIC ; 
 int /*<<< orphan*/  SQLITE_MAX_LENGTH ; 
 int WHERE_AUTO_INDEX ; 
 int WHERE_BOTH_LIMIT ; 
 int WHERE_BTM_LIMIT ; 
 int WHERE_COLUMN_EQ ; 
 int WHERE_COLUMN_IN ; 
 int WHERE_CONSTRAINT ; 
 int WHERE_IDX_ONLY ; 
 int WHERE_IPK ; 
 int WHERE_MULTI_OR ; 
 int WHERE_ORDERBY_MAX ; 
 int WHERE_ORDERBY_MIN ; 
 int WHERE_OR_SUBCLAUSE ; 
 int WHERE_PARTIALIDX ; 
 int WHERE_TOP_LIMIT ; 
 int WHERE_VIRTUALTABLE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  explainIndexRange (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  sqlite3ExplainBreakpoint (char*,char*) ; 
 char const* sqlite3LogEstToInt (int) ; 
 TYPE_13__* sqlite3ParseToplevel (TYPE_8__*) ; 
 char* sqlite3StrAccumFinish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3StrAccumInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int sqlite3VdbeAddOp4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeCurrentAddr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_str_append (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sqlite3_str_appendall (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sqlite3_str_appendf (int /*<<< orphan*/ *,char const*,char const*,...) ; 

int sqlite3WhereExplainOneScan(
  Parse *pParse,                  /* Parse context */
  SrcList *pTabList,              /* Table list this loop refers to */
  WhereLevel *pLevel,             /* Scan to write OP_Explain opcode for */
  u16 wctrlFlags                  /* Flags passed to sqlite3WhereBegin() */
){
  int ret = 0;
#if !defined(SQLITE_DEBUG) && !defined(SQLITE_ENABLE_STMT_SCANSTATUS)
  if( sqlite3ParseToplevel(pParse)->explain==2 )
#endif
  {
    struct SrcList_item *pItem = &pTabList->a[pLevel->iFrom];
    Vdbe *v = pParse->pVdbe;      /* VM being constructed */
    sqlite3 *db = pParse->db;     /* Database handle */
    int isSearch;                 /* True for a SEARCH. False for SCAN. */
    WhereLoop *pLoop;             /* The controlling WhereLoop object */
    u32 flags;                    /* Flags that describe this loop */
    char *zMsg;                   /* Text to add to EQP output */
    StrAccum str;                 /* EQP output string */
    char zBuf[100];               /* Initial space for EQP output string */

    pLoop = pLevel->pWLoop;
    flags = pLoop->wsFlags;
    if( (flags&WHERE_MULTI_OR) || (wctrlFlags&WHERE_OR_SUBCLAUSE) ) return 0;

    isSearch = (flags&(WHERE_BTM_LIMIT|WHERE_TOP_LIMIT))!=0
            || ((flags&WHERE_VIRTUALTABLE)==0 && (pLoop->u.btree.nEq>0))
            || (wctrlFlags&(WHERE_ORDERBY_MIN|WHERE_ORDERBY_MAX));

    sqlite3StrAccumInit(&str, db, zBuf, sizeof(zBuf), SQLITE_MAX_LENGTH);
    sqlite3_str_appendall(&str, isSearch ? "SEARCH" : "SCAN");
    if( pItem->pSelect ){
      sqlite3_str_appendf(&str, " SUBQUERY %u", pItem->pSelect->selId);
    }else{
      sqlite3_str_appendf(&str, " TABLE %s", pItem->zName);
    }

    if( pItem->zAlias ){
      sqlite3_str_appendf(&str, " AS %s", pItem->zAlias);
    }
    if( (flags & (WHERE_IPK|WHERE_VIRTUALTABLE))==0 ){
      const char *zFmt = 0;
      Index *pIdx;

      assert( pLoop->u.btree.pIndex!=0 );
      pIdx = pLoop->u.btree.pIndex;
      assert( !(flags&WHERE_AUTO_INDEX) || (flags&WHERE_IDX_ONLY) );
      if( !HasRowid(pItem->pTab) && IsPrimaryKeyIndex(pIdx) ){
        if( isSearch ){
          zFmt = "PRIMARY KEY";
        }
      }else if( flags & WHERE_PARTIALIDX ){
        zFmt = "AUTOMATIC PARTIAL COVERING INDEX";
      }else if( flags & WHERE_AUTO_INDEX ){
        zFmt = "AUTOMATIC COVERING INDEX";
      }else if( flags & WHERE_IDX_ONLY ){
        zFmt = "COVERING INDEX %s";
      }else{
        zFmt = "INDEX %s";
      }
      if( zFmt ){
        sqlite3_str_append(&str, " USING ", 7);
        sqlite3_str_appendf(&str, zFmt, pIdx->zName);
        explainIndexRange(&str, pLoop);
      }
    }else if( (flags & WHERE_IPK)!=0 && (flags & WHERE_CONSTRAINT)!=0 ){
      const char *zRangeOp;
      if( flags&(WHERE_COLUMN_EQ|WHERE_COLUMN_IN) ){
        zRangeOp = "=";
      }else if( (flags&WHERE_BOTH_LIMIT)==WHERE_BOTH_LIMIT ){
        zRangeOp = ">? AND rowid<";
      }else if( flags&WHERE_BTM_LIMIT ){
        zRangeOp = ">";
      }else{
        assert( flags&WHERE_TOP_LIMIT);
        zRangeOp = "<";
      }
      sqlite3_str_appendf(&str, 
          " USING INTEGER PRIMARY KEY (rowid%s?)",zRangeOp);
    }
#ifndef SQLITE_OMIT_VIRTUALTABLE
    else if( (flags & WHERE_VIRTUALTABLE)!=0 ){
      sqlite3_str_appendf(&str, " VIRTUAL TABLE INDEX %d:%s",
                  pLoop->u.vtab.idxNum, pLoop->u.vtab.idxStr);
    }
#endif
#ifdef SQLITE_EXPLAIN_ESTIMATED_ROWS
    if( pLoop->nOut>=10 ){
      sqlite3_str_appendf(&str, " (~%llu rows)",
             sqlite3LogEstToInt(pLoop->nOut));
    }else{
      sqlite3_str_append(&str, " (~1 row)", 9);
    }
#endif
    zMsg = sqlite3StrAccumFinish(&str);
    sqlite3ExplainBreakpoint("",zMsg);
    ret = sqlite3VdbeAddOp4(v, OP_Explain, sqlite3VdbeCurrentAddr(v),
                            pParse->addrExplain, 0, zMsg,P4_DYNAMIC);
  }
  return ret;
}