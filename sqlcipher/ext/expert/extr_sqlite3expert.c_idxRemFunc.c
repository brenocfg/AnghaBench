#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct IdxRemSlot {int eType; char* z; int n; int nByte; int /*<<< orphan*/  rVal; int /*<<< orphan*/  iVal; } ;
struct IdxRemCtx {int nSlot; struct IdxRemSlot* aSlot; } ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;

/* Variables and functions */
#define  SQLITE_BLOB 132 
#define  SQLITE_FLOAT 131 
#define  SQLITE_INTEGER 130 
#define  SQLITE_NULL 129 
#define  SQLITE_TEXT 128 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sqlite3_realloc (char*,int) ; 
 int /*<<< orphan*/  sqlite3_result_blob (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_double (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_error_nomem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_user_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_value_blob (int /*<<< orphan*/ *) ; 
 int sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_value_double (int /*<<< orphan*/ *) ; 
 int sqlite3_value_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_value_int64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_value_text (int /*<<< orphan*/ *) ; 
 int sqlite3_value_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void idxRemFunc(
  sqlite3_context *pCtx,
  int argc,
  sqlite3_value **argv
){
  struct IdxRemCtx *p = (struct IdxRemCtx*)sqlite3_user_data(pCtx);
  struct IdxRemSlot *pSlot;
  int iSlot;
  assert( argc==2 );

  iSlot = sqlite3_value_int(argv[0]);
  assert( iSlot<=p->nSlot );
  pSlot = &p->aSlot[iSlot];

  switch( pSlot->eType ){
    case SQLITE_NULL:
      /* no-op */
      break;

    case SQLITE_INTEGER:
      sqlite3_result_int64(pCtx, pSlot->iVal);
      break;

    case SQLITE_FLOAT:
      sqlite3_result_double(pCtx, pSlot->rVal);
      break;

    case SQLITE_BLOB:
      sqlite3_result_blob(pCtx, pSlot->z, pSlot->n, SQLITE_TRANSIENT);
      break;

    case SQLITE_TEXT:
      sqlite3_result_text(pCtx, pSlot->z, pSlot->n, SQLITE_TRANSIENT);
      break;
  }

  pSlot->eType = sqlite3_value_type(argv[1]);
  switch( pSlot->eType ){
    case SQLITE_NULL:
      /* no-op */
      break;

    case SQLITE_INTEGER:
      pSlot->iVal = sqlite3_value_int64(argv[1]);
      break;

    case SQLITE_FLOAT:
      pSlot->rVal = sqlite3_value_double(argv[1]);
      break;

    case SQLITE_BLOB:
    case SQLITE_TEXT: {
      int nByte = sqlite3_value_bytes(argv[1]);
      if( nByte>pSlot->nByte ){
        char *zNew = (char*)sqlite3_realloc(pSlot->z, nByte*2);
        if( zNew==0 ){
          sqlite3_result_error_nomem(pCtx);
          return;
        }
        pSlot->nByte = nByte*2;
        pSlot->z = zNew;
      }
      pSlot->n = nByte;
      if( pSlot->eType==SQLITE_BLOB ){
        memcpy(pSlot->z, sqlite3_value_blob(argv[1]), nByte);
      }else{
        memcpy(pSlot->z, sqlite3_value_text(argv[1]), nByte);
      }
      break;
    }
  }
}