#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vfs ;
typedef  scalar_t__ sqlite3_uint64 ;
struct TYPE_8__ {int /*<<< orphan*/ * pMethods; } ;
typedef  TYPE_1__ sqlite3_file ;
struct TYPE_9__ {scalar_t__ iNextFileId; } ;
typedef  TYPE_2__ VfslogVfs ;
struct TYPE_10__ {scalar_t__ iFileId; TYPE_1__* pReal; int /*<<< orphan*/ * pVfslog; } ;
typedef  TYPE_3__ VfslogFile ;
struct TYPE_11__ {int (* xOpen ) (TYPE_5__*,char const*,TYPE_1__*,int,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  OS_OPEN ; 
 TYPE_5__* REALVFS (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_5__*,char const*,TYPE_1__*,int,int*) ; 
 int /*<<< orphan*/  vfslog_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfslog_io_methods ; 
 int /*<<< orphan*/  vfslog_string (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ vfslog_time () ; 

__attribute__((used)) static int vfslogOpen(
  sqlite3_vfs *pVfs,
  const char *zName,
  sqlite3_file *pFile,
  int flags,
  int *pOutFlags
){
  int rc;
  sqlite3_uint64 t;
  VfslogFile *p = (VfslogFile *)pFile;
  VfslogVfs *pLog = (VfslogVfs *)pVfs;

  pFile->pMethods = &vfslog_io_methods;
  p->pReal = (sqlite3_file *)&p[1];
  p->pVfslog = pVfs;
  p->iFileId = ++pLog->iNextFileId;

  t = vfslog_time();
  rc = REALVFS(pVfs)->xOpen(REALVFS(pVfs), zName, p->pReal, flags, pOutFlags);
  t = vfslog_time() - t;

  vfslog_call(pVfs, OS_OPEN, p->iFileId, t, rc, 0, 0);
  vfslog_string(pVfs, zName);
  return rc;
}