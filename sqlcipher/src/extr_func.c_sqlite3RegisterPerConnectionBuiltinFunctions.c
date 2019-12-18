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
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_TEXT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3CreateFunc (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void (*) (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **),int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3OomFault (int /*<<< orphan*/ *) ; 
 int sqlite3_overload_function (int /*<<< orphan*/ *,char*,int) ; 

void sqlite3RegisterPerConnectionBuiltinFunctions(sqlite3 *db){
  int rc = sqlite3_overload_function(db, "MATCH", 2);
/* BEGIN SQLCIPHER */
#ifdef SQLITE_HAS_CODEC
#ifndef OMIT_EXPORT
  extern void sqlcipher_exportFunc(sqlite3_context *, int, sqlite3_value **);
#endif
#endif
/* END SQLCIPHER */
  assert( rc==SQLITE_NOMEM || rc==SQLITE_OK );
  if( rc==SQLITE_NOMEM ){
    sqlite3OomFault(db);
  }
/* BEGIN SQLCIPHER */
#ifdef SQLITE_HAS_CODEC
#ifndef OMIT_EXPORT
  sqlite3CreateFunc(db, "sqlcipher_export", -1, SQLITE_TEXT, 0, sqlcipher_exportFunc, 0, 0, 0, 0, 0);
#endif
#endif
/* END SQLCIPHER */
}