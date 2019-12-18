#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_3__ {int /*<<< orphan*/  pGlobal; } ;
typedef  int /*<<< orphan*/  Fts5Cursor ;
typedef  TYPE_1__ Fts5Auxiliary ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts5ApiInvoke (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * fts5CursorFromCsrid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ sqlite3_user_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_value_int64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fts5ApiCallback(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){

  Fts5Auxiliary *pAux;
  Fts5Cursor *pCsr;
  i64 iCsrId;

  assert( argc>=1 );
  pAux = (Fts5Auxiliary*)sqlite3_user_data(context);
  iCsrId = sqlite3_value_int64(argv[0]);

  pCsr = fts5CursorFromCsrid(pAux->pGlobal, iCsrId);
  if( pCsr==0 ){
    char *zErr = sqlite3_mprintf("no such cursor: %lld", iCsrId);
    sqlite3_result_error(context, zErr, -1);
    sqlite3_free(zErr);
  }else{
    fts5ApiInvoke(pAux, pCsr, context, argc-1, &argv[1]);
  }
}