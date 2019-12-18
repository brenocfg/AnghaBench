#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sqlite3_int64 ;
struct TYPE_8__ {int /*<<< orphan*/  nSegment; } ;
struct TYPE_7__ {int nLeafEst; int iIdx; int /*<<< orphan*/  iStart; TYPE_1__* aNodeWriter; int /*<<< orphan*/  iAbsLevel; scalar_t__ iEnd; } ;
struct TYPE_6__ {scalar_t__ iBlock; } ;
typedef  TYPE_2__ IncrmergeWriter ;
typedef  int /*<<< orphan*/  Fts3Table ;
typedef  TYPE_3__ Fts3MultiSegReader ;

/* Variables and functions */
 int FTS_MAX_APPENDABLE_HEIGHT ; 
 int SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  SQL_MAX_LEAF_NODE_ESTIMATE ; 
 int /*<<< orphan*/  SQL_NEXT_SEGMENTS_ID ; 
 int fts3SqlStmt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int fts3WriteSegment (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_int64 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int sqlite3_column_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_column_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3_reset (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts3IncrmergeWriter( 
  Fts3Table *p,                   /* Fts3 table handle */
  sqlite3_int64 iAbsLevel,        /* Absolute level of input segments */
  int iIdx,                       /* Index of new output segment */
  Fts3MultiSegReader *pCsr,       /* Cursor that data will be read from */
  IncrmergeWriter *pWriter        /* Populate this object */
){
  int rc;                         /* Return Code */
  int i;                          /* Iterator variable */
  int nLeafEst = 0;               /* Blocks allocated for leaf nodes */
  sqlite3_stmt *pLeafEst = 0;     /* SQL used to determine nLeafEst */
  sqlite3_stmt *pFirstBlock = 0;  /* SQL used to determine first block */

  /* Calculate nLeafEst. */
  rc = fts3SqlStmt(p, SQL_MAX_LEAF_NODE_ESTIMATE, &pLeafEst, 0);
  if( rc==SQLITE_OK ){
    sqlite3_bind_int64(pLeafEst, 1, iAbsLevel);
    sqlite3_bind_int64(pLeafEst, 2, pCsr->nSegment);
    if( SQLITE_ROW==sqlite3_step(pLeafEst) ){
      nLeafEst = sqlite3_column_int(pLeafEst, 0);
    }
    rc = sqlite3_reset(pLeafEst);
  }
  if( rc!=SQLITE_OK ) return rc;

  /* Calculate the first block to use in the output segment */
  rc = fts3SqlStmt(p, SQL_NEXT_SEGMENTS_ID, &pFirstBlock, 0);
  if( rc==SQLITE_OK ){
    if( SQLITE_ROW==sqlite3_step(pFirstBlock) ){
      pWriter->iStart = sqlite3_column_int64(pFirstBlock, 0);
      pWriter->iEnd = pWriter->iStart - 1;
      pWriter->iEnd += nLeafEst * FTS_MAX_APPENDABLE_HEIGHT;
    }
    rc = sqlite3_reset(pFirstBlock);
  }
  if( rc!=SQLITE_OK ) return rc;

  /* Insert the marker in the %_segments table to make sure nobody tries
  ** to steal the space just allocated. This is also used to identify 
  ** appendable segments.  */
  rc = fts3WriteSegment(p, pWriter->iEnd, 0, 0);
  if( rc!=SQLITE_OK ) return rc;

  pWriter->iAbsLevel = iAbsLevel;
  pWriter->nLeafEst = nLeafEst;
  pWriter->iIdx = iIdx;

  /* Set up the array of NodeWriter objects */
  for(i=0; i<FTS_MAX_APPENDABLE_HEIGHT; i++){
    pWriter->aNodeWriter[i].iBlock = pWriter->iStart + i*pWriter->nLeafEst;
  }
  return SQLITE_OK;
}