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
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int /*<<< orphan*/  pPtr ;
typedef  int /*<<< orphan*/  fts2Hash ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  assert (int) ; 
 void* sqlite3Fts2HashFind (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 void* sqlite3Fts2HashInsert (int /*<<< orphan*/ *,void*,int,void*) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,unsigned char const*) ; 
 int /*<<< orphan*/  sqlite3_result_blob (int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ sqlite3_user_data (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_blob (int /*<<< orphan*/ *) ; 
 int sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 unsigned char* sqlite3_value_text (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void scalarFunc(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  fts2Hash *pHash;
  void *pPtr = 0;
  const unsigned char *zName;
  int nName;

  assert( argc==1 || argc==2 );

  pHash = (fts2Hash *)sqlite3_user_data(context);

  zName = sqlite3_value_text(argv[0]);
  nName = sqlite3_value_bytes(argv[0])+1;

  if( argc==2 ){
    void *pOld;
    int n = sqlite3_value_bytes(argv[1]);
    if( n!=sizeof(pPtr) ){
      sqlite3_result_error(context, "argument type mismatch", -1);
      return;
    }
    pPtr = *(void **)sqlite3_value_blob(argv[1]);
    pOld = sqlite3Fts2HashInsert(pHash, (void *)zName, nName, pPtr);
    if( pOld==pPtr ){
      sqlite3_result_error(context, "out of memory", -1);
      return;
    }
  }else{
    pPtr = sqlite3Fts2HashFind(pHash, zName, nName);
    if( !pPtr ){
      char *zErr = sqlite3_mprintf("unknown tokenizer: %s", zName);
      sqlite3_result_error(context, zErr, -1);
      sqlite3_free(zErr);
      return;
    }
  }

  sqlite3_result_blob(context, (void *)&pPtr, sizeof(pPtr), SQLITE_TRANSIENT);
}