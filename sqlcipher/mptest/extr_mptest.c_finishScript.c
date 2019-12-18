#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  runSql (char*,int) ; 

__attribute__((used)) static int finishScript(int iClient, int taskId, int bShutdown){
  runSql("UPDATE task"
         "   SET endtime=strftime('%%Y-%%m-%%d %%H:%%M:%%f','now')"
         " WHERE id=%d;", taskId);
  if( bShutdown ){
    runSql("DELETE FROM client WHERE id=%d", iClient);
  }
  return SQLITE_OK;
}