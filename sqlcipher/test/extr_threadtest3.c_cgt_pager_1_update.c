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
typedef  int i64 ;
typedef  int /*<<< orphan*/  Sqlite ;
typedef  int /*<<< orphan*/  Error ;

/* Variables and functions */
 int CALLGRINDTEST1_NROW ; 
 int /*<<< orphan*/  execsql (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int*,int*) ; 
 int /*<<< orphan*/  sql_script (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void cgt_pager_1_update(Error *pErr, Sqlite *pDb){
  const char *zUpdate = "UPDATE t1 SET b = zeroblob(:iBlob) WHERE a = :iRow";
  i64 iRow;
  sql_script(pErr, pDb, "BEGIN");
  for(iRow=1; iRow<=CALLGRINDTEST1_NROW; iRow++){
    i64 iBlob = 600 + ((iRow+100)%300);
    execsql(pErr, pDb, zUpdate, &iBlob, &iRow);
  }
  sql_script(pErr, pDb, "COMMIT");
}