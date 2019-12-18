#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int /*<<< orphan*/  fts5_api ;
struct TYPE_2__ {int /*<<< orphan*/  api; } ;
typedef  TYPE_1__ Fts5Global ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAM (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ sqlite3_user_data (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_pointer (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void fts5Fts5Func(
  sqlite3_context *pCtx,          /* Function call context */
  int nArg,                       /* Number of args */
  sqlite3_value **apArg           /* Function arguments */
){
  Fts5Global *pGlobal = (Fts5Global*)sqlite3_user_data(pCtx);
  fts5_api **ppApi;
  UNUSED_PARAM(nArg);
  assert( nArg==1 );
  ppApi = (fts5_api**)sqlite3_value_pointer(apArg[0], "fts5_api_ptr");
  if( ppApi ) *ppApi = &pGlobal->api;
}