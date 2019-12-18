#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_4__ {int /*<<< orphan*/  pVfs; } ;
typedef  TYPE_1__ sqlite3 ;
typedef  scalar_t__ i64 ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_FCNTL_MMAP_SIZE ; 
 int SQLITE_IOERR_ACCESS ; 
 scalar_t__ SQLITE_MAX_MMAP_SIZE ; 
 int SQLITE_OK ; 
 int SQLITE_OPEN_CREATE ; 
 int SQLITE_OPEN_DELETEONCLOSE ; 
 int SQLITE_OPEN_EXCLUSIVE ; 
 int SQLITE_OPEN_READWRITE ; 
 int SQLITE_OPEN_TEMP_JOURNAL ; 
 scalar_t__ sqlite3FaultSim (int) ; 
 int /*<<< orphan*/  sqlite3OsFileControlHint (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int sqlite3OsOpenMalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int,int*) ; 
 int /*<<< orphan*/  vdbeSorterExtendFile (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int vdbeSorterOpenTempFile(
  sqlite3 *db,                    /* Database handle doing sort */
  i64 nExtend,                    /* Attempt to extend file to this size */
  sqlite3_file **ppFd
){
  int rc;
  if( sqlite3FaultSim(202) ) return SQLITE_IOERR_ACCESS;
  rc = sqlite3OsOpenMalloc(db->pVfs, 0, ppFd,
      SQLITE_OPEN_TEMP_JOURNAL |
      SQLITE_OPEN_READWRITE    | SQLITE_OPEN_CREATE |
      SQLITE_OPEN_EXCLUSIVE    | SQLITE_OPEN_DELETEONCLOSE, &rc
  );
  if( rc==SQLITE_OK ){
    i64 max = SQLITE_MAX_MMAP_SIZE;
    sqlite3OsFileControlHint(*ppFd, SQLITE_FCNTL_MMAP_SIZE, (void*)&max);
    if( nExtend>0 ){
      vdbeSorterExtendFile(db, *ppFd, nExtend);
    }
  }
  return rc;
}