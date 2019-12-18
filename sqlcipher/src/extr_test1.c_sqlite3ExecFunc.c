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
typedef  int /*<<< orphan*/  x ;
struct dstr {int /*<<< orphan*/  z; int /*<<< orphan*/  nUsed; } ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  execFuncCallback ; 
 int /*<<< orphan*/  memset (struct dstr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_exec (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,struct dstr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_user_data (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sqlite3ExecFunc(
  sqlite3_context *context, 
  int argc,  
  sqlite3_value **argv
){
  struct dstr x;
  memset(&x, 0, sizeof(x));
  (void)sqlite3_exec((sqlite3*)sqlite3_user_data(context),
      (char*)sqlite3_value_text(argv[0]),
      execFuncCallback, &x, 0);
  sqlite3_result_text(context, x.z, x.nUsed, SQLITE_TRANSIENT);
  sqlite3_free(x.z);
}