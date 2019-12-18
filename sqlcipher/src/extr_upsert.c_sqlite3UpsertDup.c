#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_5__ {int /*<<< orphan*/  pUpsertWhere; int /*<<< orphan*/  pUpsertSet; int /*<<< orphan*/  pUpsertTargetWhere; int /*<<< orphan*/  pUpsertTarget; } ;
typedef  TYPE_1__ Upsert ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3ExprDup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ExprListDup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* sqlite3UpsertNew (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Upsert *sqlite3UpsertDup(sqlite3 *db, Upsert *p){
  if( p==0 ) return 0;
  return sqlite3UpsertNew(db,
           sqlite3ExprListDup(db, p->pUpsertTarget, 0),
           sqlite3ExprDup(db, p->pUpsertTargetWhere, 0),
           sqlite3ExprListDup(db, p->pUpsertSet, 0),
           sqlite3ExprDup(db, p->pUpsertWhere, 0)
         );
}