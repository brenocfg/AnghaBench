#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int iDb; scalar_t__ busy; } ;
struct TYPE_13__ {int mDbFlags; TYPE_1__ init; } ;
typedef  TYPE_2__ sqlite3 ;
struct TYPE_14__ {scalar_t__ n; } ;
typedef  TYPE_3__ Token ;
struct TYPE_15__ {TYPE_2__* db; } ;
typedef  TYPE_4__ Parse ;

/* Variables and functions */
 int DBFLAG_Vacuum ; 
 scalar_t__ IN_RENAME_OBJECT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3ErrorMsg (TYPE_4__*,char*,...) ; 
 int sqlite3FindDb (TYPE_2__*,TYPE_3__*) ; 

int sqlite3TwoPartName(
  Parse *pParse,      /* Parsing and code generating context */
  Token *pName1,      /* The "xxx" in the name "xxx.yyy" or "xxx" */
  Token *pName2,      /* The "yyy" in the name "xxx.yyy" */
  Token **pUnqual     /* Write the unqualified object name here */
){
  int iDb;                    /* Database holding the object */
  sqlite3 *db = pParse->db;

  assert( pName2!=0 );
  if( pName2->n>0 ){
    if( db->init.busy ) {
      sqlite3ErrorMsg(pParse, "corrupt database");
      return -1;
    }
    *pUnqual = pName2;
    iDb = sqlite3FindDb(db, pName1);
    if( iDb<0 ){
      sqlite3ErrorMsg(pParse, "unknown database %T", pName1);
      return -1;
    }
  }else{
    assert( db->init.iDb==0 || db->init.busy || IN_RENAME_OBJECT
             || (db->mDbFlags & DBFLAG_Vacuum)!=0);
    iDb = db->init.iDb;
    *pUnqual = pName1;
  }
  return iDb;
}