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
struct TYPE_7__ {TYPE_1__* pMethods; } ;
typedef  TYPE_2__ sqlite3_file ;
struct TYPE_6__ {int (* xFileControl ) (TYPE_2__*,int,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DO_OS_MALLOC_TEST (TYPE_2__*) ; 
 int SQLITE_FCNTL_COMMIT_PHASETWO ; 
 int SQLITE_FCNTL_LOCK_TIMEOUT ; 
 int SQLITE_NOTFOUND ; 
 int stub1 (TYPE_2__*,int,void*) ; 

int sqlite3OsFileControl(sqlite3_file *id, int op, void *pArg){
  if( id->pMethods==0 ) return SQLITE_NOTFOUND;
#ifdef SQLITE_TEST
  if( op!=SQLITE_FCNTL_COMMIT_PHASETWO
   && op!=SQLITE_FCNTL_LOCK_TIMEOUT
  ){
    /* Faults are not injected into COMMIT_PHASETWO because, assuming SQLite
    ** is using a regular VFS, it is called after the corresponding
    ** transaction has been committed. Injecting a fault at this point
    ** confuses the test scripts - the COMMIT comand returns SQLITE_NOMEM
    ** but the transaction is committed anyway.
    **
    ** The core must call OsFileControl() though, not OsFileControlHint(),
    ** as if a custom VFS (e.g. zipvfs) returns an error here, it probably
    ** means the commit really has failed and an error should be returned
    ** to the user.  */
    DO_OS_MALLOC_TEST(id);
  }
#endif
  return id->pMethods->xFileControl(id, op, pArg);
}