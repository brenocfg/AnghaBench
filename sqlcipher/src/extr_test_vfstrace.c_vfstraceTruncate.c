#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  zVfsName; } ;
typedef  TYPE_2__ vfstrace_info ;
struct TYPE_8__ {TYPE_5__* pReal; int /*<<< orphan*/  zFName; TYPE_2__* pInfo; } ;
typedef  TYPE_3__ vfstrace_file ;
typedef  int /*<<< orphan*/  sqlite_int64 ;
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_9__ {TYPE_1__* pMethods; } ;
struct TYPE_6__ {int (* xTruncate ) (TYPE_5__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfstrace_printf (TYPE_2__*,char*,int,...) ; 

__attribute__((used)) static int vfstraceTruncate(sqlite3_file *pFile, sqlite_int64 size){
  vfstrace_file *p = (vfstrace_file *)pFile;
  vfstrace_info *pInfo = p->pInfo;
  int rc;
  vfstrace_printf(pInfo, "%s.xTruncate(%s,%lld)", pInfo->zVfsName, p->zFName,
                  size);
  rc = p->pReal->pMethods->xTruncate(p->pReal, size);
  vfstrace_printf(pInfo, " -> %d\n", rc);
  return rc;
}