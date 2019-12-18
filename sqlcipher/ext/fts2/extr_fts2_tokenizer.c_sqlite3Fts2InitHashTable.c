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
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  fts2Hash ;

/* Variables and functions */
 int SQLITE_ANY ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  intTestFunc ; 
 int /*<<< orphan*/  scalarFunc ; 
 int sqlite3_create_function (int /*<<< orphan*/ *,char const*,int,int const,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char const*) ; 
 int /*<<< orphan*/  testFunc ; 

int sqlite3Fts2InitHashTable(
  sqlite3 *db, 
  fts2Hash *pHash, 
  const char *zName
){
  int rc = SQLITE_OK;
  void *p = (void *)pHash;
  const int any = SQLITE_ANY;
  char *zTest = 0;
  char *zTest2 = 0;

#ifdef SQLITE_TEST
  void *pdb = (void *)db;
  zTest = sqlite3_mprintf("%s_test", zName);
  zTest2 = sqlite3_mprintf("%s_internal_test", zName);
  if( !zTest || !zTest2 ){
    rc = SQLITE_NOMEM;
  }
#endif

  if( rc!=SQLITE_OK
   || (rc = sqlite3_create_function(db, zName, 1, any, p, scalarFunc, 0, 0))
   || (rc = sqlite3_create_function(db, zName, 2, any, p, scalarFunc, 0, 0))
#ifdef SQLITE_TEST
   || (rc = sqlite3_create_function(db, zTest, 2, any, p, testFunc, 0, 0))
   || (rc = sqlite3_create_function(db, zTest, 3, any, p, testFunc, 0, 0))
   || (rc = sqlite3_create_function(db, zTest2, 0, any, pdb, intTestFunc, 0, 0))
#endif
  );

  sqlite3_free(zTest);
  sqlite3_free(zTest2);
  return rc;
}