#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_5__ {TYPE_3__* pReal; } ;
typedef  TYPE_2__ rbu_file ;
struct TYPE_6__ {TYPE_1__* pMethods; } ;
struct TYPE_4__ {int (* xSectorSize ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int stub1 (TYPE_3__*) ; 

__attribute__((used)) static int rbuVfsSectorSize(sqlite3_file *pFile){
  rbu_file *p = (rbu_file *)pFile;
  return p->pReal->pMethods->xSectorSize(p->pReal);
}