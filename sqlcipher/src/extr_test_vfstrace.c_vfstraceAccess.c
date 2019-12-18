#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  zVfsName; TYPE_2__* pRootVfs; } ;
typedef  TYPE_1__ vfstrace_info ;
struct TYPE_8__ {int (* xAccess ) (TYPE_2__*,char const*,int,int*) ;scalar_t__ pAppData; } ;
typedef  TYPE_2__ sqlite3_vfs ;

/* Variables and functions */
 int stub1 (TYPE_2__*,char const*,int,int*) ; 
 int /*<<< orphan*/  vfstrace_print_errcode (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  vfstrace_printf (TYPE_1__*,char*,int,...) ; 

__attribute__((used)) static int vfstraceAccess(
  sqlite3_vfs *pVfs, 
  const char *zPath, 
  int flags, 
  int *pResOut
){
  vfstrace_info *pInfo = (vfstrace_info*)pVfs->pAppData;
  sqlite3_vfs *pRoot = pInfo->pRootVfs;
  int rc;
  vfstrace_printf(pInfo, "%s.xAccess(\"%s\",%d)",
                  pInfo->zVfsName, zPath, flags);
  rc = pRoot->xAccess(pRoot, zPath, flags, pResOut);
  vfstrace_print_errcode(pInfo, " -> %s", rc);
  vfstrace_printf(pInfo, ", out=%d\n", *pResOut);
  return rc;
}