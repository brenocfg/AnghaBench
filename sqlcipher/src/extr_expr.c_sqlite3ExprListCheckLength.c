#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int nExpr; } ;
struct TYPE_8__ {TYPE_1__* db; } ;
struct TYPE_7__ {int* aLimit; } ;
typedef  TYPE_2__ Parse ;
typedef  TYPE_3__ ExprList ;

/* Variables and functions */
 size_t SQLITE_LIMIT_COLUMN ; 
 int /*<<< orphan*/  sqlite3ErrorMsg (TYPE_2__*,char*,char const*) ; 
 int /*<<< orphan*/  testcase (int /*<<< orphan*/ ) ; 

void sqlite3ExprListCheckLength(
  Parse *pParse,
  ExprList *pEList,
  const char *zObject
){
  int mx = pParse->db->aLimit[SQLITE_LIMIT_COLUMN];
  testcase( pEList && pEList->nExpr==mx );
  testcase( pEList && pEList->nExpr==mx+1 );
  if( pEList && pEList->nExpr>mx ){
    sqlite3ErrorMsg(pParse, "too many columns in %s", zObject);
  }
}