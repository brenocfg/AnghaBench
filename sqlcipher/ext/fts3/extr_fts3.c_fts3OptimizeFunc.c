#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_4__ {scalar_t__ pVtab; } ;
struct TYPE_5__ {TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  Fts3Table ;
typedef  TYPE_2__ Fts3Cursor ;

/* Variables and functions */
#define  SQLITE_DONE 129 
#define  SQLITE_OK 128 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ fts3FunctionArg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,TYPE_2__**) ; 
 int sqlite3Fts3Optimize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_error_code (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fts3OptimizeFunc(
  sqlite3_context *pContext,      /* SQLite function call context */
  int nVal,                       /* Size of argument array */
  sqlite3_value **apVal           /* Array of arguments */
){
  int rc;                         /* Return code */
  Fts3Table *p;                   /* Virtual table handle */
  Fts3Cursor *pCursor;            /* Cursor handle passed through apVal[0] */

  UNUSED_PARAMETER(nVal);

  assert( nVal==1 );
  if( fts3FunctionArg(pContext, "optimize", apVal[0], &pCursor) ) return;
  p = (Fts3Table *)pCursor->base.pVtab;
  assert( p );

  rc = sqlite3Fts3Optimize(p);

  switch( rc ){
    case SQLITE_OK:
      sqlite3_result_text(pContext, "Index optimized", -1, SQLITE_STATIC);
      break;
    case SQLITE_DONE:
      sqlite3_result_text(pContext, "Index already optimal", -1, SQLITE_STATIC);
      break;
    default:
      sqlite3_result_error_code(pContext, rc);
      break;
  }
}