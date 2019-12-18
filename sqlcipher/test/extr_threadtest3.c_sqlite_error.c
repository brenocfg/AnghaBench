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
struct TYPE_6__ {int /*<<< orphan*/  zErr; int /*<<< orphan*/  rc; } ;
struct TYPE_5__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ Sqlite ;
typedef  TYPE_2__ Error ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3_errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_extended_errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mprintf (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sqlite_error(
  Error *pErr, 
  Sqlite *pDb, 
  const char *zFunc
){
  pErr->rc = sqlite3_errcode(pDb->db);
  pErr->zErr = sqlite3_mprintf(
      "sqlite3_%s() - %s (%d)", zFunc, sqlite3_errmsg(pDb->db),
      sqlite3_extended_errcode(pDb->db)
  );
}