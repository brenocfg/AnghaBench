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
struct TYPE_7__ {scalar_t__ bDisable; } ;
struct TYPE_8__ {TYPE_1__ lookaside; } ;
typedef  TYPE_2__ sqlite3 ;
struct TYPE_9__ {scalar_t__ disableLookaside; int /*<<< orphan*/  pConstExpr; int /*<<< orphan*/  aLabel; TYPE_2__* db; } ;
typedef  TYPE_3__ Parse ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3DbFree (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ExprListDelete (TYPE_2__*,int /*<<< orphan*/ ) ; 

void sqlite3ParserReset(Parse *pParse){
  sqlite3 *db = pParse->db;
  sqlite3DbFree(db, pParse->aLabel);
  sqlite3ExprListDelete(db, pParse->pConstExpr);
  if( db ){
    assert( db->lookaside.bDisable >= pParse->disableLookaside );
    db->lookaside.bDisable -= pParse->disableLookaside;
  }
  pParse->disableLookaside = 0;
}