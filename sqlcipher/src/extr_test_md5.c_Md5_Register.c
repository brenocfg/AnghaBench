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
typedef  int /*<<< orphan*/  sqlite3_api_routines ;
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_UTF8 ; 
 int /*<<< orphan*/  md5finalize ; 
 int /*<<< orphan*/  md5step ; 
 int sqlite3_create_function (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_overload_function (int /*<<< orphan*/ *,char*,int) ; 

int Md5_Register(
  sqlite3 *db,
  char **pzErrMsg,
  const sqlite3_api_routines *pThunk
){
  int rc = sqlite3_create_function(db, "md5sum", -1, SQLITE_UTF8, 0, 0,
                                 md5step, md5finalize);
  sqlite3_overload_function(db, "md5sum", -1);  /* To exercise this API */
  return rc;
}