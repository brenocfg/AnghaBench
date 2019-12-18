#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ rc; int /*<<< orphan*/  zErr; } ;
struct TYPE_5__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ Sqlite ;
typedef  TYPE_2__ Error ;

/* Variables and functions */
 scalar_t__ SQLITE_OK ; 
 scalar_t__ sqlite3_exec (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sql_script_x(
  Error *pErr,                    /* IN/OUT: Error code */
  Sqlite *pDb,                    /* Database handle */
  const char *zSql                /* SQL script to execute */
){
  if( pErr->rc==SQLITE_OK ){
    pErr->rc = sqlite3_exec(pDb->db, zSql, 0, 0, &pErr->zErr);
  }
}