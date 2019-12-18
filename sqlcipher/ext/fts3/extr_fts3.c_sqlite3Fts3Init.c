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
typedef  int /*<<< orphan*/  sqlite3_tokenizer_module ;
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  Fts3Hash ;

/* Variables and functions */
 int /*<<< orphan*/  FTS3_HASH_STRING ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts3Module ; 
 int /*<<< orphan*/  hashDestroy ; 
 int sqlite3Fts3ExprInitTestInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3Fts3HashClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3Fts3HashInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sqlite3Fts3HashInsert (int /*<<< orphan*/ *,char*,int,void*) ; 
 int /*<<< orphan*/  sqlite3Fts3IcuTokenizerModule (int /*<<< orphan*/  const**) ; 
 int sqlite3Fts3InitAux (int /*<<< orphan*/ *) ; 
 int sqlite3Fts3InitHashTable (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int sqlite3Fts3InitTerm (int /*<<< orphan*/ *) ; 
 int sqlite3Fts3InitTok (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  sqlite3Fts3PorterTokenizerModule (int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  sqlite3Fts3SimpleTokenizerModule (int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  sqlite3Fts3UnicodeTokenizer (int /*<<< orphan*/  const**) ; 
 int sqlite3_create_module_v2 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3_malloc (int) ; 
 int sqlite3_overload_function (int /*<<< orphan*/ *,char*,int) ; 

int sqlite3Fts3Init(sqlite3 *db){
  int rc = SQLITE_OK;
  Fts3Hash *pHash = 0;
  const sqlite3_tokenizer_module *pSimple = 0;
  const sqlite3_tokenizer_module *pPorter = 0;
#ifndef SQLITE_DISABLE_FTS3_UNICODE
  const sqlite3_tokenizer_module *pUnicode = 0;
#endif

#ifdef SQLITE_ENABLE_ICU
  const sqlite3_tokenizer_module *pIcu = 0;
  sqlite3Fts3IcuTokenizerModule(&pIcu);
#endif

#ifndef SQLITE_DISABLE_FTS3_UNICODE
  sqlite3Fts3UnicodeTokenizer(&pUnicode);
#endif

#ifdef SQLITE_TEST
  rc = sqlite3Fts3InitTerm(db);
  if( rc!=SQLITE_OK ) return rc;
#endif

  rc = sqlite3Fts3InitAux(db);
  if( rc!=SQLITE_OK ) return rc;

  sqlite3Fts3SimpleTokenizerModule(&pSimple);
  sqlite3Fts3PorterTokenizerModule(&pPorter);

  /* Allocate and initialize the hash-table used to store tokenizers. */
  pHash = sqlite3_malloc(sizeof(Fts3Hash));
  if( !pHash ){
    rc = SQLITE_NOMEM;
  }else{
    sqlite3Fts3HashInit(pHash, FTS3_HASH_STRING, 1);
  }

  /* Load the built-in tokenizers into the hash table */
  if( rc==SQLITE_OK ){
    if( sqlite3Fts3HashInsert(pHash, "simple", 7, (void *)pSimple)
     || sqlite3Fts3HashInsert(pHash, "porter", 7, (void *)pPorter) 

#ifndef SQLITE_DISABLE_FTS3_UNICODE
     || sqlite3Fts3HashInsert(pHash, "unicode61", 10, (void *)pUnicode) 
#endif
#ifdef SQLITE_ENABLE_ICU
     || (pIcu && sqlite3Fts3HashInsert(pHash, "icu", 4, (void *)pIcu))
#endif
    ){
      rc = SQLITE_NOMEM;
    }
  }

#ifdef SQLITE_TEST
  if( rc==SQLITE_OK ){
    rc = sqlite3Fts3ExprInitTestInterface(db, pHash);
  }
#endif

  /* Create the virtual table wrapper around the hash-table and overload 
  ** the four scalar functions. If this is successful, register the
  ** module with sqlite.
  */
  if( SQLITE_OK==rc 
   && SQLITE_OK==(rc = sqlite3Fts3InitHashTable(db, pHash, "fts3_tokenizer"))
   && SQLITE_OK==(rc = sqlite3_overload_function(db, "snippet", -1))
   && SQLITE_OK==(rc = sqlite3_overload_function(db, "offsets", 1))
   && SQLITE_OK==(rc = sqlite3_overload_function(db, "matchinfo", 1))
   && SQLITE_OK==(rc = sqlite3_overload_function(db, "matchinfo", 2))
   && SQLITE_OK==(rc = sqlite3_overload_function(db, "optimize", 1))
  ){
    rc = sqlite3_create_module_v2(
        db, "fts3", &fts3Module, (void *)pHash, hashDestroy
    );
    if( rc==SQLITE_OK ){
      rc = sqlite3_create_module_v2(
          db, "fts4", &fts3Module, (void *)pHash, 0
      );
    }
    if( rc==SQLITE_OK ){
      rc = sqlite3Fts3InitTok(db, (void *)pHash);
    }
    return rc;
  }


  /* An error has occurred. Delete the hash table and return the error code. */
  assert( rc!=SQLITE_OK );
  if( pHash ){
    sqlite3Fts3HashClear(pHash);
    sqlite3_free(pHash);
  }
  return rc;
}