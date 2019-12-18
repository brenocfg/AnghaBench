#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct Db {scalar_t__ pBt; struct Db* zDbSName; } ;
struct TYPE_4__ {int nDb; struct Db* aDbStatic; struct Db* aDb; } ;
typedef  TYPE_1__ sqlite3 ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct Db*,struct Db*,int) ; 
 int /*<<< orphan*/  sqlite3DbFree (TYPE_1__*,struct Db*) ; 

void sqlite3CollapseDatabaseArray(sqlite3 *db){
  int i, j;
  for(i=j=2; i<db->nDb; i++){
    struct Db *pDb = &db->aDb[i];
    if( pDb->pBt==0 ){
      sqlite3DbFree(db, pDb->zDbSName);
      pDb->zDbSName = 0;
      continue;
    }
    if( j<i ){
      db->aDb[j] = db->aDb[i];
    }
    j++;
  }
  db->nDb = j;
  if( db->nDb<=2 && db->aDb!=db->aDbStatic ){
    memcpy(db->aDbStatic, db->aDb, 2*sizeof(db->aDb[0]));
    sqlite3DbFree(db, db->aDb);
    db->aDb = db->aDbStatic;
  }
}