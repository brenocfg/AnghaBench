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

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_UTF8 ; 
 int /*<<< orphan*/  fts5DecodeFunction ; 
 int /*<<< orphan*/  fts5RowidFunction ; 
 int sqlite3_create_function (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sqlite3Fts5IndexInit(sqlite3 *db){
  int rc = sqlite3_create_function(
      db, "fts5_decode", 2, SQLITE_UTF8, 0, fts5DecodeFunction, 0, 0
  );

  if( rc==SQLITE_OK ){
    rc = sqlite3_create_function(
        db, "fts5_decode_none", 2, 
        SQLITE_UTF8, (void*)db, fts5DecodeFunction, 0, 0
    );
  }

  if( rc==SQLITE_OK ){
    rc = sqlite3_create_function(
        db, "fts5_rowid", -1, SQLITE_UTF8, 0, fts5RowidFunction, 0, 0
    );
  }
  return rc;
}