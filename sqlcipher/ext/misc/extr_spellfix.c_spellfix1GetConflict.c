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
 int SQLITE_ABORT ; 
 int SQLITE_FAIL ; 
 int SQLITE_IGNORE ; 
 int SQLITE_REPLACE ; 
 int SQLITE_ROLLBACK ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3_vtab_on_conflict (int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *spellfix1GetConflict(sqlite3 *db){
  static const char *azConflict[] = {
    /* Note: Instead of "FAIL" - "ABORT". */
    "ROLLBACK", "IGNORE", "ABORT", "ABORT", "REPLACE"
  };
  int eConflict = sqlite3_vtab_on_conflict(db);

  assert( eConflict==SQLITE_ROLLBACK || eConflict==SQLITE_IGNORE
       || eConflict==SQLITE_FAIL || eConflict==SQLITE_ABORT
       || eConflict==SQLITE_REPLACE
  );
  assert( SQLITE_ROLLBACK==1 );
  assert( SQLITE_IGNORE==2 );
  assert( SQLITE_FAIL==3 );
  assert( SQLITE_ABORT==4 );
  assert( SQLITE_REPLACE==5 );

  return azConflict[eConflict-1];
}