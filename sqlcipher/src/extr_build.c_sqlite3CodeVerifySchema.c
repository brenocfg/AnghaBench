#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int nDb; TYPE_1__* aDb; } ;
struct TYPE_9__ {int /*<<< orphan*/  cookieMask; TYPE_3__* db; } ;
struct TYPE_8__ {scalar_t__ pBt; } ;
typedef  TYPE_2__ Parse ;

/* Variables and functions */
 int /*<<< orphan*/  DbMaskSet (int /*<<< orphan*/ ,int) ; 
 scalar_t__ DbMaskTest (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OMIT_TEMPDB ; 
 int SQLITE_MAX_ATTACHED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3OpenTempDatabase (TYPE_2__*) ; 
 TYPE_2__* sqlite3ParseToplevel (TYPE_2__*) ; 
 int sqlite3SchemaMutexHeld (TYPE_3__*,int,int /*<<< orphan*/ ) ; 

void sqlite3CodeVerifySchema(Parse *pParse, int iDb){
  Parse *pToplevel = sqlite3ParseToplevel(pParse);

  assert( iDb>=0 && iDb<pParse->db->nDb );
  assert( pParse->db->aDb[iDb].pBt!=0 || iDb==1 );
  assert( iDb<SQLITE_MAX_ATTACHED+2 );
  assert( sqlite3SchemaMutexHeld(pParse->db, iDb, 0) );
  if( DbMaskTest(pToplevel->cookieMask, iDb)==0 ){
    DbMaskSet(pToplevel->cookieMask, iDb);
    if( !OMIT_TEMPDB && iDb==1 ){
      sqlite3OpenTempDatabase(pToplevel);
    }
  }
}