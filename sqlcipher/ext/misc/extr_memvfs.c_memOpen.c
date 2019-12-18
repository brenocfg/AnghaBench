#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vfs ;
struct TYPE_5__ {int /*<<< orphan*/ * pMethods; } ;
typedef  TYPE_1__ sqlite3_file ;
struct TYPE_6__ {unsigned char* aData; scalar_t__ sz; scalar_t__ szMax; int /*<<< orphan*/  bFreeOnClose; } ;
typedef  TYPE_2__ MemFile ;

/* Variables and functions */
 int SQLITE_CANTOPEN ; 
 int SQLITE_OK ; 
 int SQLITE_OPEN_MAIN_DB ; 
 int /*<<< orphan*/  mem_io_methods ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_uri_boolean (char const*,char*,int /*<<< orphan*/ ) ; 
 void* sqlite3_uri_int64 (char const*,char*,scalar_t__) ; 

__attribute__((used)) static int memOpen(
  sqlite3_vfs *pVfs,
  const char *zName,
  sqlite3_file *pFile,
  int flags,
  int *pOutFlags
){
  MemFile *p = (MemFile*)pFile;
  memset(p, 0, sizeof(*p));
  if( (flags & SQLITE_OPEN_MAIN_DB)==0 ) return SQLITE_CANTOPEN;
  p->aData = (unsigned char*)sqlite3_uri_int64(zName,"ptr",0);
  if( p->aData==0 ) return SQLITE_CANTOPEN;
  p->sz = sqlite3_uri_int64(zName,"sz",0);
  if( p->sz<0 ) return SQLITE_CANTOPEN;
  p->szMax = sqlite3_uri_int64(zName,"max",p->sz);
  if( p->szMax<p->sz ) return SQLITE_CANTOPEN;
  p->bFreeOnClose = sqlite3_uri_boolean(zName,"freeonclose",0);
  pFile->pMethods = &mem_io_methods;
  return SQLITE_OK;
}