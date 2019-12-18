#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  sqlite3_blob ;
struct TYPE_5__ {int /*<<< orphan*/  zDb; int /*<<< orphan*/  db; } ;
struct TYPE_4__ {int rc; int /*<<< orphan*/  zDataTbl; TYPE_2__* pConfig; } ;
typedef  TYPE_1__ Fts5Index ;
typedef  TYPE_2__ Fts5Config ;

/* Variables and functions */
 int /*<<< orphan*/  FTS5_STRUCTURE_ROWID ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3Fts5Put32 (int /*<<< orphan*/ *,int) ; 
 int sqlite3_blob_close (int /*<<< orphan*/ *) ; 
 int sqlite3_blob_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  sqlite3_blob_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int sqlite3Fts5IndexSetCookie(Fts5Index *p, int iNew){
  int rc;                              /* Return code */
  Fts5Config *pConfig = p->pConfig;    /* Configuration object */
  u8 aCookie[4];                       /* Binary representation of iNew */
  sqlite3_blob *pBlob = 0;

  assert( p->rc==SQLITE_OK );
  sqlite3Fts5Put32(aCookie, iNew);

  rc = sqlite3_blob_open(pConfig->db, pConfig->zDb, p->zDataTbl, 
      "block", FTS5_STRUCTURE_ROWID, 1, &pBlob
  );
  if( rc==SQLITE_OK ){
    sqlite3_blob_write(pBlob, aCookie, 4, 0);
    rc = sqlite3_blob_close(pBlob);
  }

  return rc;
}