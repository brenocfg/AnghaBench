#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_7__ {int eFrmType; int eStart; int eEnd; int bImplicitFrame; void* pStart; void* pEnd; scalar_t__ eExclude; } ;
typedef  TYPE_1__ Window ;
struct TYPE_8__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ Parse ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 scalar_t__ OptimizationDisabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SQLITE_WindowFunc ; 
 int TK_CURRENT ; 
 int TK_FOLLOWING ; 
 int TK_GROUPS ; 
 scalar_t__ TK_NO ; 
 int TK_PRECEDING ; 
 int TK_RANGE ; 
 int TK_ROWS ; 
 int TK_UNBOUNDED ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ sqlite3DbMallocZero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3ErrorMsg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  sqlite3ExprDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* sqlite3WindowOffsetExpr (TYPE_2__*,int /*<<< orphan*/ *) ; 

Window *sqlite3WindowAlloc(
  Parse *pParse,    /* Parsing context */
  int eType,        /* Frame type. TK_RANGE, TK_ROWS, TK_GROUPS, or 0 */
  int eStart,       /* Start type: CURRENT, PRECEDING, FOLLOWING, UNBOUNDED */
  Expr *pStart,     /* Start window size if TK_PRECEDING or FOLLOWING */
  int eEnd,         /* End type: CURRENT, FOLLOWING, TK_UNBOUNDED, PRECEDING */
  Expr *pEnd,       /* End window size if TK_FOLLOWING or PRECEDING */
  u8 eExclude       /* EXCLUDE clause */
){
  Window *pWin = 0;
  int bImplicitFrame = 0;

  /* Parser assures the following: */
  assert( eType==0 || eType==TK_RANGE || eType==TK_ROWS || eType==TK_GROUPS );
  assert( eStart==TK_CURRENT || eStart==TK_PRECEDING
           || eStart==TK_UNBOUNDED || eStart==TK_FOLLOWING );
  assert( eEnd==TK_CURRENT || eEnd==TK_FOLLOWING
           || eEnd==TK_UNBOUNDED || eEnd==TK_PRECEDING );
  assert( (eStart==TK_PRECEDING || eStart==TK_FOLLOWING)==(pStart!=0) );
  assert( (eEnd==TK_FOLLOWING || eEnd==TK_PRECEDING)==(pEnd!=0) );

  if( eType==0 ){
    bImplicitFrame = 1;
    eType = TK_RANGE;
  }

  /* Additionally, the
  ** starting boundary type may not occur earlier in the following list than
  ** the ending boundary type:
  **
  **   UNBOUNDED PRECEDING
  **   <expr> PRECEDING
  **   CURRENT ROW
  **   <expr> FOLLOWING
  **   UNBOUNDED FOLLOWING
  **
  ** The parser ensures that "UNBOUNDED PRECEDING" cannot be used as an ending
  ** boundary, and than "UNBOUNDED FOLLOWING" cannot be used as a starting
  ** frame boundary.
  */
  if( (eStart==TK_CURRENT && eEnd==TK_PRECEDING)
   || (eStart==TK_FOLLOWING && (eEnd==TK_PRECEDING || eEnd==TK_CURRENT))
  ){
    sqlite3ErrorMsg(pParse, "unsupported frame specification");
    goto windowAllocErr;
  }

  pWin = (Window*)sqlite3DbMallocZero(pParse->db, sizeof(Window));
  if( pWin==0 ) goto windowAllocErr;
  pWin->eFrmType = eType;
  pWin->eStart = eStart;
  pWin->eEnd = eEnd;
  if( eExclude==0 && OptimizationDisabled(pParse->db, SQLITE_WindowFunc) ){
    eExclude = TK_NO;
  }
  pWin->eExclude = eExclude;
  pWin->bImplicitFrame = bImplicitFrame;
  pWin->pEnd = sqlite3WindowOffsetExpr(pParse, pEnd);
  pWin->pStart = sqlite3WindowOffsetExpr(pParse, pStart);
  return pWin;

windowAllocErr:
  sqlite3ExprDelete(pParse->db, pEnd);
  sqlite3ExprDelete(pParse->db, pStart);
  return 0;
}