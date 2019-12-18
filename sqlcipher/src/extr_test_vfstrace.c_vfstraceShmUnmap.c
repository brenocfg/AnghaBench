#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  zVfsName; } ;
typedef  TYPE_2__ vfstrace_info ;
struct TYPE_9__ {TYPE_6__* pReal; int /*<<< orphan*/  zFName; TYPE_2__* pInfo; } ;
typedef  TYPE_3__ vfstrace_file ;
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_10__ {TYPE_1__* pMethods; } ;
struct TYPE_7__ {int (* xShmUnmap ) (TYPE_6__*,int) ;} ;

/* Variables and functions */
 int stub1 (TYPE_6__*,int) ; 
 int /*<<< orphan*/  vfstrace_print_errcode (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  vfstrace_printf (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vfstraceShmUnmap(sqlite3_file *pFile, int delFlag){
  vfstrace_file *p = (vfstrace_file *)pFile;
  vfstrace_info *pInfo = p->pInfo;
  int rc;
  vfstrace_printf(pInfo, "%s.xShmUnmap(%s,delFlag=%d)",
                  pInfo->zVfsName, p->zFName, delFlag);
  rc = p->pReal->pMethods->xShmUnmap(p->pReal, delFlag);
  vfstrace_print_errcode(pInfo, " -> %s\n", rc);
  return rc;
}