#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  val ;
typedef  int u8 ;
typedef  int /*<<< orphan*/  sqlite_int64 ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int sqlite3_int64 ;
typedef  int /*<<< orphan*/  r ;
struct TYPE_6__ {int nVal; int /*<<< orphan*/  pDb; int /*<<< orphan*/  keyType; } ;
typedef  TYPE_1__ lsm1_vtab ;
struct TYPE_7__ {int /*<<< orphan*/  a; int /*<<< orphan*/  n; scalar_t__ errNoMem; } ;
typedef  TYPE_2__ lsm1_vblob ;

/* Variables and functions */
 int LSM_OK ; 
#define  SQLITE_BLOB 132 
 int SQLITE_ERROR ; 
#define  SQLITE_FLOAT 131 
#define  SQLITE_INTEGER 130 
 int SQLITE_NOMEM ; 
#define  SQLITE_NULL 129 
 int SQLITE_OK ; 
#define  SQLITE_TEXT 128 
 int /*<<< orphan*/  lsm1KeyFromValue (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*,int const**,int*) ; 
 int lsm1PutSignedVarint64 (unsigned char*,int) ; 
 int /*<<< orphan*/  lsm1VblobAppend (TYPE_2__*,...) ; 
 int /*<<< orphan*/  lsm1VblobAppendVarint (TYPE_2__*,scalar_t__ const) ; 
 int /*<<< orphan*/  lsm_delete (int /*<<< orphan*/ ,int const*,int) ; 
 int lsm_insert (int /*<<< orphan*/ ,int const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int const*,int const*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ ) ; 
 int* sqlite3_value_blob (int /*<<< orphan*/ *) ; 
 int sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 double sqlite3_value_double (int /*<<< orphan*/ *) ; 
 int sqlite3_value_int64 (int /*<<< orphan*/ *) ; 
 int* sqlite3_value_text (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_type (int /*<<< orphan*/ *) ; 

int lsm1Update(
  sqlite3_vtab *pVTab,
  int argc,
  sqlite3_value **argv,
  sqlite_int64 *pRowid
){
  lsm1_vtab *p = (lsm1_vtab*)pVTab;
  int nKey, nKey2;
  int i;
  int rc = LSM_OK;
  const u8 *pKey, *pKey2;
  unsigned char aKey[16];
  unsigned char pSpace[16];
  lsm1_vblob val;

  if( argc==1 ){
    /* DELETE the record whose key is argv[0] */
    lsm1KeyFromValue(p->keyType, argv[0], aKey, &pKey, &nKey);
    lsm_delete(p->pDb, pKey, nKey);
    return SQLITE_OK;
  }

  if( sqlite3_value_type(argv[0])!=SQLITE_NULL ){
    /* An UPDATE */
    lsm1KeyFromValue(p->keyType, argv[0], aKey, &pKey, &nKey);
    lsm1KeyFromValue(p->keyType, argv[1], pSpace, &pKey2, &nKey2);
    if( nKey!=nKey2 || memcmp(pKey, pKey2, nKey)!=0 ){
      /* The UPDATE changes the PRIMARY KEY value.  DELETE the old key */
      lsm_delete(p->pDb, pKey, nKey);
    }
    /* Fall through into the INSERT case to complete the UPDATE */
  }

  /* "INSERT INTO tab(lsm1_command) VALUES('....')" is used to implement
  ** special commands.
  */
  if( sqlite3_value_type(argv[3+p->nVal])!=SQLITE_NULL ){
    return SQLITE_OK;
  }
  lsm1KeyFromValue(p->keyType, argv[2], aKey, &pKey, &nKey);
  memset(&val, 0, sizeof(val));
  for(i=0; i<p->nVal; i++){
    sqlite3_value *pArg = argv[3+i];
    u8 eType = sqlite3_value_type(pArg);
    switch( eType ){
      case SQLITE_NULL: {
        lsm1VblobAppendVarint(&val, SQLITE_NULL);
        break;
      }
      case SQLITE_INTEGER: {
        sqlite3_int64 v = sqlite3_value_int64(pArg);
        if( v>=0 && v<=240/6 ){
          lsm1VblobAppendVarint(&val, v*6);
        }else{
          int n = lsm1PutSignedVarint64(pSpace, v);
          lsm1VblobAppendVarint(&val, SQLITE_INTEGER + n*6);
          lsm1VblobAppend(&val, pSpace, n);
        }
        break;
      }
      case SQLITE_FLOAT: {
        double r = sqlite3_value_double(pArg);
        lsm1VblobAppendVarint(&val, SQLITE_FLOAT + 8*6);
        lsm1VblobAppend(&val, (u8*)&r, sizeof(r));
        break;
      }
      case SQLITE_BLOB: {
        int n = sqlite3_value_bytes(pArg);
        lsm1VblobAppendVarint(&val, n*6 + SQLITE_BLOB);
        lsm1VblobAppend(&val, sqlite3_value_blob(pArg), n);
        break;
      }
      case SQLITE_TEXT: {
        int n = sqlite3_value_bytes(pArg);
        lsm1VblobAppendVarint(&val, n*6 + SQLITE_TEXT);
        lsm1VblobAppend(&val, sqlite3_value_text(pArg), n);
        break;
      }
    }
  }
  if( val.errNoMem ){
    return SQLITE_NOMEM;
  }
  rc = lsm_insert(p->pDb, pKey, nKey, val.a, val.n);
  sqlite3_free(val.a);
  return rc==LSM_OK ? SQLITE_OK : SQLITE_ERROR;
}