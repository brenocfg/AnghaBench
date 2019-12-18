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
struct TYPE_6__ {int (* xSync ) (TYPE_2__*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DO_OS_MALLOC_TEST (TYPE_2__*) ; 
 int SQLITE_OK ; 
 int stub1 (TYPE_2__*,int) ; 

int sqlite3OsSync(sqlite3_file *id, int flags){
  DO_OS_MALLOC_TEST(id);
  return flags ? id->pMethods->xSync(id, flags) : SQLITE_OK;
}