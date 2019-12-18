#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_api_routines ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_3__ {int szOsFile; int /*<<< orphan*/  pAppData; } ;
typedef  int /*<<< orphan*/  MemFile ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_EXTENSION_INIT2 (int /*<<< orphan*/  const*) ; 
 int SQLITE_OK ; 
 int SQLITE_OK_LOAD_PERMANENTLY ; 
 TYPE_1__ mem_vfs ; 
 int memvfsRegister (int /*<<< orphan*/ *,char**,int /*<<< orphan*/  const*) ; 
 int sqlite3_auto_extension (void (*) ()) ; 
 int /*<<< orphan*/  sqlite3_vfs_find (int /*<<< orphan*/ ) ; 
 int sqlite3_vfs_register (TYPE_1__*,int) ; 

int sqlite3_memvfs_init(
  sqlite3 *db, 
  char **pzErrMsg, 
  const sqlite3_api_routines *pApi
){
  int rc = SQLITE_OK;
  SQLITE_EXTENSION_INIT2(pApi);
  mem_vfs.pAppData = sqlite3_vfs_find(0);
  mem_vfs.szOsFile = sizeof(MemFile);
  rc = sqlite3_vfs_register(&mem_vfs, 1);
#ifdef MEMVFS_TEST
  if( rc==SQLITE_OK ){
    rc = sqlite3_auto_extension((void(*)(void))memvfsRegister);
  }
  if( rc==SQLITE_OK ){
    rc = memvfsRegister(db, pzErrMsg, pApi);
  }
#endif
  if( rc==SQLITE_OK ) rc = SQLITE_OK_LOAD_PERMANENTLY;
  return rc;
}