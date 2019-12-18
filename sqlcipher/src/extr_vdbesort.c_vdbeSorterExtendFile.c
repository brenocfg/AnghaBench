#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* pMethods; } ;
typedef  TYPE_2__ sqlite3_file ;
struct TYPE_11__ {scalar_t__ nMaxSorterMmap; } ;
typedef  TYPE_3__ sqlite3 ;
typedef  scalar_t__ i64 ;
struct TYPE_9__ {int iVersion; } ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_FCNTL_CHUNK_SIZE ; 
 int /*<<< orphan*/  SQLITE_FCNTL_SIZE_HINT ; 
 int /*<<< orphan*/  sqlite3OsFetch (TYPE_2__*,int /*<<< orphan*/ ,int,void**) ; 
 int /*<<< orphan*/  sqlite3OsFileControlHint (TYPE_2__*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  sqlite3OsUnfetch (TYPE_2__*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void vdbeSorterExtendFile(sqlite3 *db, sqlite3_file *pFd, i64 nByte){
  if( nByte<=(i64)(db->nMaxSorterMmap) && pFd->pMethods->iVersion>=3 ){
    void *p = 0;
    int chunksize = 4*1024;
    sqlite3OsFileControlHint(pFd, SQLITE_FCNTL_CHUNK_SIZE, &chunksize);
    sqlite3OsFileControlHint(pFd, SQLITE_FCNTL_SIZE_HINT, &nByte);
    sqlite3OsFetch(pFd, 0, (int)nByte, &p);
    sqlite3OsUnfetch(pFd, 0, p);
  }
}