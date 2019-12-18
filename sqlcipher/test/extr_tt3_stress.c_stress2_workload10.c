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
 int /*<<< orphan*/  sql_script_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void stress2_workload10(Error *pErr, Sqlite *pDb, int i){
  sql_script_printf(pErr, pDb,
      "DELETE FROM t0 WHERE x LIKE hex(%d %% 5) AND z='big';", i
  );
}