#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ pReader; struct TYPE_5__* zDataTbl; int /*<<< orphan*/  pHash; int /*<<< orphan*/  pDataVersion; int /*<<< orphan*/  pIdxSelect; int /*<<< orphan*/  pIdxDeleter; int /*<<< orphan*/  pIdxWriter; int /*<<< orphan*/  pDeleter; int /*<<< orphan*/  pWriter; } ;
typedef  TYPE_1__ Fts5Index ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts5StructureInvalidate (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3Fts5HashFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 

int sqlite3Fts5IndexClose(Fts5Index *p){
  int rc = SQLITE_OK;
  if( p ){
    assert( p->pReader==0 );
    fts5StructureInvalidate(p);
    sqlite3_finalize(p->pWriter);
    sqlite3_finalize(p->pDeleter);
    sqlite3_finalize(p->pIdxWriter);
    sqlite3_finalize(p->pIdxDeleter);
    sqlite3_finalize(p->pIdxSelect);
    sqlite3_finalize(p->pDataVersion);
    sqlite3Fts5HashFree(p->pHash);
    sqlite3_free(p->zDataTbl);
    sqlite3_free(p);
  }
  return rc;
}