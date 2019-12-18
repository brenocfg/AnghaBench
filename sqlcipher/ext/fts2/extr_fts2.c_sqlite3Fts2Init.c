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
typedef  int /*<<< orphan*/  fts2Hash ;

/* Variables and functions */
 int /*<<< orphan*/  FTS2_HASH_STRING ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts2Module ; 
 int /*<<< orphan*/  hashDestroy ; 
 int /*<<< orphan*/  sqlite3Fts2HashClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3Fts2HashInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sqlite3Fts2HashInsert (int /*<<< orphan*/ *,char*,int,void*) ; 
 int /*<<< orphan*/  sqlite3Fts2IcuTokenizerModule (int /*<<< orphan*/  const**) ; 
 int sqlite3Fts2InitHashTable (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sqlite3Fts2PorterTokenizerModule (int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  sqlite3Fts2SimpleTokenizerModule (int /*<<< orphan*/  const**) ; 
 int sqlite3_create_module_v2 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3_malloc (int) ; 
 int sqlite3_overload_function (int /*<<< orphan*/ *,char*,int) ; 

int sqlite3Fts2Init(sqlite3 *db){
  int rc = SQLITE_OK;
  fts2Hash *pHash = 0;
  const sqlite3_tokenizer_module *pSimple = 0;
  const sqlite3_tokenizer_module *pPorter = 0;
  const sqlite3_tokenizer_module *pIcu = 0;

  sqlite3Fts2SimpleTokenizerModule(&pSimple);
  sqlite3Fts2PorterTokenizerModule(&pPorter);
#ifdef SQLITE_ENABLE_ICU
  sqlite3Fts2IcuTokenizerModule(&pIcu);
#endif

  /* Allocate and initialize the hash-table used to store tokenizers. */
  pHash = sqlite3_malloc(sizeof(fts2Hash));
  if( !pHash ){
    rc = SQLITE_NOMEM;
  }else{
    sqlite3Fts2HashInit(pHash, FTS2_HASH_STRING, 1);
  }

  /* Load the built-in tokenizers into the hash table */
  if( rc==SQLITE_OK ){
    if( sqlite3Fts2HashInsert(pHash, "simple", 7, (void *)pSimple)
     || sqlite3Fts2HashInsert(pHash, "porter", 7, (void *)pPorter) 
     || (pIcu && sqlite3Fts2HashInsert(pHash, "icu", 4, (void *)pIcu))
    ){
      rc = SQLITE_NOMEM;
    }
  }

  /* Create the virtual table wrapper around the hash-table and overload 
  ** the two scalar functions. If this is successful, register the
  ** module with sqlite.
  */
  if( SQLITE_OK==rc 
   && SQLITE_OK==(rc = sqlite3Fts2InitHashTable(db, pHash, "fts2_tokenizer"))
   && SQLITE_OK==(rc = sqlite3_overload_function(db, "snippet", -1))
   && SQLITE_OK==(rc = sqlite3_overload_function(db, "offsets", -1))
   && SQLITE_OK==(rc = sqlite3_overload_function(db, "optimize", -1))
#ifdef SQLITE_TEST
   && SQLITE_OK==(rc = sqlite3_overload_function(db, "dump_terms", -1))
   && SQLITE_OK==(rc = sqlite3_overload_function(db, "dump_doclist", -1))
#endif
  ){
    return sqlite3_create_module_v2(
        db, "fts2", &fts2Module, (void *)pHash, hashDestroy
    );
  }

  /* An error has occurred. Delete the hash table and return the error code. */
  assert( rc!=SQLITE_OK );
  if( pHash ){
    sqlite3Fts2HashClear(pHash);
    sqlite3_free(pHash);
  }
  return rc;
}