#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_3__ {int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ CidxTable ;

/* Variables and functions */
 int SQLITE_OK ; 
 TYPE_1__* cidxMalloc (int*,int) ; 
 int sqlite3_declare_vtab (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int cidxConnect(
  sqlite3 *db,
  void *pAux,
  int argc, const char *const*argv,
  sqlite3_vtab **ppVtab,
  char **pzErr
){
  int rc = SQLITE_OK;
  CidxTable *pRet;

#define IIC_ERRMSG        0
#define IIC_CURRENT_KEY   1
#define IIC_INDEX_NAME    2
#define IIC_AFTER_KEY     3
#define IIC_SCANNER_SQL   4
  rc = sqlite3_declare_vtab(db,
      "CREATE TABLE xyz("
      " errmsg TEXT,"            /* Error message or NULL if everything is ok */
      " current_key TEXT,"       /* SQLite quote() text of key values */
      " index_name HIDDEN,"      /* IN: name of the index being scanned */
      " after_key HIDDEN,"       /* IN: Start scanning after this key */
      " scanner_sql HIDDEN"      /* debuggingn info: SQL used for scanner */
      ")"
  );
  pRet = cidxMalloc(&rc, sizeof(CidxTable));
  if( pRet ){
    pRet->db = db;
  }

  *ppVtab = (sqlite3_vtab*)pRet;
  return rc;
}