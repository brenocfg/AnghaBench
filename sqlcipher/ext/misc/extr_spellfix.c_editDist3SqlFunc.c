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
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  EditDist3Lang ;
typedef  int /*<<< orphan*/  EditDist3FromString ;
typedef  int /*<<< orphan*/  EditDist3Config ;

/* Variables and functions */
 int editDist3ConfigLoad (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int editDist3Core (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * editDist3FindLang (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  editDist3FromStringDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * editDist3FromStringNew (int /*<<< orphan*/  const*,char const*,int) ; 
 int /*<<< orphan*/ * sqlite3_context_db_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_error_code (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_result_error_nomem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_int (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_user_data (int /*<<< orphan*/ *) ; 
 int sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 int sqlite3_value_int (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void editDist3SqlFunc(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  EditDist3Config *pConfig = (EditDist3Config*)sqlite3_user_data(context);
  sqlite3 *db = sqlite3_context_db_handle(context);
  int rc;
  if( argc==1 ){
    const char *zTable = (const char*)sqlite3_value_text(argv[0]);
    rc = editDist3ConfigLoad(pConfig, db, zTable);
    if( rc ) sqlite3_result_error_code(context, rc);
  }else{
    const char *zA = (const char*)sqlite3_value_text(argv[0]);
    const char *zB = (const char*)sqlite3_value_text(argv[1]);
    int nA = sqlite3_value_bytes(argv[0]);
    int nB = sqlite3_value_bytes(argv[1]);
    int iLang = argc==3 ? sqlite3_value_int(argv[2]) : 0;
    const EditDist3Lang *pLang = editDist3FindLang(pConfig, iLang);
    EditDist3FromString *pFrom;
    int dist;

    pFrom = editDist3FromStringNew(pLang, zA, nA);
    if( pFrom==0 ){
      sqlite3_result_error_nomem(context);
      return;
    }
    dist = editDist3Core(pFrom, zB, nB, pLang, 0);
    editDist3FromStringDelete(pFrom);
    if( dist==(-1) ){
      sqlite3_result_error_nomem(context);
    }else{
      sqlite3_result_int(context, dist);
    }
  } 
}