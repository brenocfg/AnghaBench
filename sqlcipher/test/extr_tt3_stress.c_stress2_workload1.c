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
typedef  int /*<<< orphan*/  Sqlite ;
typedef  int /*<<< orphan*/  Error ;

/* Variables and functions */
 int STRESS2_TABCNT ; 
 int /*<<< orphan*/  sql_script_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void stress2_workload1(Error *pErr, Sqlite *pDb, int i){
  int iTab = (i % (STRESS2_TABCNT-1)) + 1;
  sql_script_printf(pErr, pDb, 
      "CREATE TABLE IF NOT EXISTS t%d(x PRIMARY KEY, y, z);", iTab
  );
}