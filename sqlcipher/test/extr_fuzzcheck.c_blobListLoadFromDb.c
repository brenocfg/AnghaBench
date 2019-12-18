#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_4__ {int sz; struct TYPE_4__* pNext; scalar_t__* a; int /*<<< orphan*/  seq; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ Blob ;

/* Variables and functions */
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  fatalError (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* safe_realloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_column_blob (int /*<<< orphan*/ *,int) ; 
 int sqlite3_column_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_column_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char const*,...) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void blobListLoadFromDb(
  sqlite3 *db,             /* Read from this database */
  const char *zSql,        /* Query used to extract the blobs */
  int onlyId,              /* Only load where id is this value */
  int *pN,                 /* OUT: Write number of blobs loaded here */
  Blob **ppList            /* OUT: Write the head of the blob list here */
){
  Blob head;
  Blob *p;
  sqlite3_stmt *pStmt;
  int n = 0;
  int rc;
  char *z2;

  if( onlyId>0 ){
    z2 = sqlite3_mprintf("%s WHERE rowid=%d", zSql, onlyId);
  }else{
    z2 = sqlite3_mprintf("%s", zSql);
  }
  rc = sqlite3_prepare_v2(db, z2, -1, &pStmt, 0);
  sqlite3_free(z2);
  if( rc ) fatalError("%s", sqlite3_errmsg(db));
  head.pNext = 0;
  p = &head;
  while( SQLITE_ROW==sqlite3_step(pStmt) ){
    int sz = sqlite3_column_bytes(pStmt, 1);
    Blob *pNew = safe_realloc(0, sizeof(*pNew)+sz );
    pNew->id = sqlite3_column_int(pStmt, 0);
    pNew->sz = sz;
    pNew->seq = n++;
    pNew->pNext = 0;
    memcpy(pNew->a, sqlite3_column_blob(pStmt,1), sz);
    pNew->a[sz] = 0;
    p->pNext = pNew;
    p = pNew;
  }
  sqlite3_finalize(pStmt);
  *pN = n;
  *ppList = head.pNext;
}