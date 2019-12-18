#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fulltext_vtab ;
struct TYPE_5__ {scalar_t__ pData; } ;
struct TYPE_6__ {int eof; int /*<<< orphan*/  leafReader; int /*<<< orphan*/  pStmt; TYPE_1__ rootData; } ;
typedef  TYPE_2__ LeavesReader ;

/* Variables and functions */
 int SQLITE_DONE ; 
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ leafReaderAtEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  leafReaderDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  leafReaderInit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  leafReaderStep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  leavesReaderAtEnd (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3_column_blob (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_column_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sqlite3_step (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int leavesReaderStep(fulltext_vtab *v, LeavesReader *pReader){
  assert( !leavesReaderAtEnd(pReader) );
  leafReaderStep(&pReader->leafReader);

  if( leafReaderAtEnd(&pReader->leafReader) ){
    int rc;
    if( pReader->rootData.pData ){
      pReader->eof = 1;
      return SQLITE_OK;
    }
    rc = sqlite3_step(pReader->pStmt);
    if( rc!=SQLITE_ROW ){
      pReader->eof = 1;
      return rc==SQLITE_DONE ? SQLITE_OK : rc;
    }
    leafReaderDestroy(&pReader->leafReader);
    leafReaderInit(sqlite3_column_blob(pReader->pStmt, 0),
                   sqlite3_column_bytes(pReader->pStmt, 0),
                   &pReader->leafReader);
  }
  return SQLITE_OK;
}